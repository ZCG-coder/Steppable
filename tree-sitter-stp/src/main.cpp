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

#include "argParse.hpp"
#include "colors.hpp"
#include "output.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpInteractive.hpp"
#include "stpInterp/stpProcessor.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

extern "C" {
#include <tree_sitter/api.h>
}

using namespace std::literals;
using namespace steppable::parser;
using namespace steppable;

extern "C" TSLanguage* tree_sitter_stp();

// void handleMemberAccess(TSNode* maNode, STP_InterpState state) {}

bool STP_isPureType(const std::string_view& str)
{
    return str == "matrix" or str == "number" or str == "string" or str == "identifier";
}

int main(int argc, const char** argv) // NOLINT(*-exception-escape)
{
    using namespace steppable::utils;

    int ret = 0;

    TSParser* parser = ts_parser_new();
    TSTree* tree = nullptr;
    ts_parser_set_language(parser, tree_sitter_stp());

    TSNode rootNode;

    std::ifstream file;
    std::string source;

    const STP_InterpState& state = STP_getState();
    std::string path;

    ProgramArgs program(argc, argv);
    program.addPosArg('p', "Path to STP file", false);

    STP_init();

    if (argc == 1)
    {
        if (isInputTerminal())
        {
            // Start interactive mode
            state->setInteractive();
            state->setFile("<interactive>");

            ret = STP_startInteractiveMode(argc, argv, state, parser);
            goto end;
        }
        else
        {
            // Read from stdin
            for (std::string line; std::getline(std::cin, line);)
                source += line + "\n";
        }
    }
    else
    {
        program.parseArgs();
        path = program.getPosArg(0);

        state->setFile(path);
        // Read the entire file at once
        file = std::ifstream(path, std::ios::in | std::ios::binary);
        if (not file)
        {
            ret = 1;
            output::error("parser"s, "Unable to open file {0}"s, { path });
            goto end;
        }

        std::array<char, 32> buffer{};
        file.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = file.gcount();
        std::string firstPart(buffer.data(), bytesRead);
        if (const size_t offset = stringUtils::findFirstNonUtf8(firstPart); std::cmp_less(offset, bytesRead))
        {
            output::error("parser"s, "Input is not UTF-8!"s);
            output::info("parser"s,
                         "\\x{0} at offset {1} is not valid UTF-8"s,
                         {
                             stringUtils::intToHex(firstPart[offset]),
                             std::to_string(offset),
                         });

            ret = 1;
            file.close();
            goto end;
        }

        std::string rest;
        if (file)
        { // If not at EOF
            rest.assign(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());
        }
        source = firstPart + rest;

        file.close();
    }

    tree = ts_parser_parse_string(parser, nullptr, source.c_str(), static_cast<uint32_t>(source.size()));
    rootNode = ts_tree_root_node(tree);
    state->setChunk(source, 0, static_cast<long>(source.size()));
    if (STP_checkRecursiveNodeSanity(rootNode, state))
        return 1;

    STP_processChunkChild(rootNode, state);

end:
    if (tree != nullptr)
        ts_tree_delete(tree);
    ts_parser_delete(parser);

    STP_destroy();

    return ret;
}
