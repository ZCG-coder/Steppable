/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

#include "output.hpp"
#include "platform.hpp"
#include "replxx.hxx"
#include "steppable/stpTypeName.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpInterrupt.hpp"
#include "stpInterp/stpProcessor.hpp"
#include "tree_sitter/api.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std::literals;

namespace steppable::parser
{
    using Replxx = replxx::Replxx;
    using namespace replxx::color;
    using namespace std::placeholders;

    using ColorMap = std::map<std::string, Replxx::Color>;

    // NOLINTNEXTLINE(cert-err58-cpp)
    static const ColorMap STP_colorMap = {
        { "keyword", Replxx::Color::BRIGHTMAGENTA }, { "number", Replxx::Color::YELLOW },
        { "function", Replxx::Color::CYAN },         { "comment", Replxx::Color::BROWN },
        { "string", Replxx::Color::GREEN },          { "string.escape", Replxx::Color::BRIGHTGREEN }
    };

    void STP_interactiveHookColor(std::string const& context,
                                  Replxx::colors_t& colors,
                                  TSParser* parser,
                                  const std::string& querySource)
    {
        colors.assign(context.length(), replxx::Replxx::Color::DEFAULT); // Default color for all characters

        TSQueryMatch match;
        uint32_t captureIdx = 0;
        const TSLanguage* language = ts_parser_language(parser);
        TSQueryCursor* cursor = ts_query_cursor_new();
        uint32_t errOffset = 0;
        TSQueryError errType{};

        TSTree* tree = ts_parser_parse_string(parser, nullptr, context.c_str(), static_cast<uint32_t>(context.size()));
        TSQuery* query = ts_query_new(language, querySource.c_str(), querySource.length(), &errOffset, &errType);
        ts_query_cursor_exec(cursor, query, ts_tree_root_node(tree));
        if (errType != TSQueryErrorNone)
            return;

        while (ts_query_cursor_next_capture(cursor, &match, &captureIdx))
        {
            for (uint16_t i = 0; i < match.capture_count; i++)
            {
                TSNode node = match.captures[i].node;
                uint32_t start = ts_node_start_byte(node);
                uint32_t end = ts_node_end_byte(node);

                uint32_t captureNameLen = 0;
                const char* captureName = ts_query_capture_name_for_id(query, match.captures[i].index, &captureNameLen);
                std::string captureNameS(captureName, captureName + captureNameLen);
                Replxx::Color color = Replxx::Color::DEFAULT;
                if (STP_colorMap.contains(captureNameS))
                    color = STP_colorMap.at(captureNameS);

                for (uint32_t i = start; i < end; i++)
                    colors[i] = color;
            }
        }
        ts_query_delete(query);
        ts_query_cursor_delete(cursor);
        ts_tree_delete(tree);
    }

    int STP_startInteractiveMode(int argc, const char** argv, const STP_InterpState& state, TSParser* parser)
    {
        std::cout << "Steppable " STEPPABLE_VERSION "\n";
        std::cout << "Written by Andy Zhang, licensed under MIT license (C) 2023-2025.\n";
        std::cout << "* For more information, type `license()`.\n";
        std::cout << "* Type an expression to evaluate. `exit` to quit.\n";

        std::string source;
        std::stringstream querySource;
        std::ifstream queryFileStream(utils::getBinDir() / "queries" / "highlights.scm");
        querySource << queryFileStream.rdbuf();

        Replxx rx;
        rx.set_highlighter_callback([&](auto&& PH1, auto&& PH2) {
            STP_interactiveHookColor(
                std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2), parser, querySource.str());
        });
        rx.set_max_history_size(1024);

        std::thread thread;
        std::atomic<TSTree*> tree = nullptr;
        STP_addCtrlCHandler([&]() {
            state->setExecState(STP_ExecState::REQUEST_STOP);
            std::cout << "BREAK\n";
        });

        while (state->getExecState() != STP_ExecState::EXIT)
        {
            state->setExecState(STP_ExecState::NORMAL);
            source.clear();

            if (char const* inputText = rx.input(": "); inputText != nullptr)
                source = inputText;
            else if (errno == EAGAIN)
            {
                // only allow exit with `exit`.
                output::info("parser"s, "Type `exit` or [Ctrl-D] to exit."s);
                continue;
            }
            else
                break;
            rx.history_add(source);

            thread = std::thread([&]() -> void {
                tree = ts_parser_parse_string(parser, nullptr, source.c_str(), static_cast<uint32_t>(source.size()));
                TSNode rootNode = ts_tree_root_node(tree);
                state->setChunk(source, 0, static_cast<long>(source.size()));
                if (STP_checkRecursiveNodeSanity(rootNode, state))
                    return;

                STP_processChunkChild(rootNode, state);
                ts_tree_delete(tree);
            });
            if (thread.joinable())
                thread.join();
        }
        return 0;
    }
} // namespace steppable::parser
