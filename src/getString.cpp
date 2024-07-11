/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

#include "getString.hpp"

#include "output.hpp"
#include "platform.hpp"
#include "util.hpp"

#include <algorithm>
#include <regex>

// DO NOT LOCALIZE

namespace steppable::localization
{
    using namespace steppable::__internals::utils;
    using namespace steppable::__internals::stringUtils;

    std::string getLanguage()
    {
        // Get the language of the system
        // On Windows, we use GetUserDefaultUILanguage
        // On macOS, we use getenv("LANG")
        // If we cannot find the language, return "en"

        std::string lang;
#ifdef WINDOWS
        LANGID langId = GetUserDefaultUILanguage();
        WCHAR localeName[LOCALE_NAME_MAX_LENGTH];

        if (LCIDToLocaleName(langId, localeName, LOCALE_NAME_MAX_LENGTH, 0) != 0)
        {
            // Convert WCHAR to std::string
            char localeNameStr[LOCALE_NAME_MAX_LENGTH];
            WideCharToMultiByte(CP_UTF8, 0, localeName, -1, localeNameStr, LOCALE_NAME_MAX_LENGTH, NULL, NULL);
            lang = std::string(localeNameStr);
        }
        else
            return "en-US";
#else
        std::string langC = getenv("LANG"); // NOLINT(concurrency-mt-unsafe)
        if (not langC.empty())
            lang = langC;

        // If the language contains a period, remove everything after the period. Eg., en-US.UTF-8 -> en-US
        auto splitResult = split(lang, '.');
        if (splitResult.size() > 1)
            lang = splitResult.front();
#endif
        // The languages may be in xx_YY format. We need to convert it to xx-YY format.
        std::ranges::replace(lang, '_', '-');
        // We cannot find the language, so we return "en-US" as the default language.
        if (lang.empty())
            lang = "en-US";
        return lang;
    }

    std::string $(const std::string& origin, const std::string& key)
    {
        // Get localization directory -> origin -> key -> **string**
        // If we cannot find the string, return the default string.
        // Localization is in <configuration directory>/translations/<language>/<origin>.stp_localized

        // Group 1: Key, Group 2: String
        const std::regex STRING_REGEX(
            R"(^([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}) >> \"([^\"]+?)\"$)");

        const auto& confDir = getConfDirectory();
        const auto& lang = getLanguage();

        const auto& langDir = confDir / "translations" / lang;
        const auto& originFile = langDir / (origin + ".stp_localized");

        if (not exists(originFile))
        {
            // If the file does not exist, we return the key as the string. Also, we log an error.
            output::error("getString"s, "Cannot find the localization file: " + originFile.string());
            return "<"s + key + ">"s; // Since the key is in UUID format, we need to make it look like a placeholder.
        }

        // Read the file and get the string
        std::ifstream file(originFile);
        if (not file.is_open())
        {
            // If we cannot open the file, we return the key as the string. Also, we log an error.
            output::error("getString"s, "Cannot open the localization file: " + originFile.string());
            return "<"s + key + ">"s; // Since the key is in UUID format, we need to make it look like a placeholder.
        }

        std::string line;
        std::string translation;
        while (std::getline(file, line))
        {
            // LINE FORMAT
            // key >> "string"
            if (line.front() == '#')
                continue; // Skip comments
            if (line.empty())
                continue; // Skip empty lines
            // Get the key and the string
            if (std::regex_match(line, STRING_REGEX))
            {
                std::smatch match;
                std::regex_search(line, match, STRING_REGEX);
                if (match.size() == 3)
                {
                    if (match[1].str() == key)
                    {
                        translation = match[2].str();
                        break;
                    }
                }
            }
            else
            {
                output::error("getString"s,
                              "Malformed line in localization file: " + originFile.string() + " -> " + line);
                break;
            }
        }

        // If we cannot find the string, we return the key as the string. Also, we log an error.
        if (translation.empty())
        {
            output::error("getString"s, "Cannot find the string for the key: " + key);
            return "<" + key + ">"; // Since the key is in UUID format, we need to make it look like a placeholder.
        }
        return translation;
    }
} // namespace steppable::localization
