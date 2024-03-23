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

#include "exceptions.hpp"

#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

// ASCII codes (key>0): 8 backspace, 9 tab, 10 newline, 27 escape, 127 delete,
// !"#$%&'()*+,-./0-9:;<=>?@A-Z[]^_`a-z{|}~üäÄöÖÜßµ´§°¹³² control key codes
// (key<0): -38/-40/-37/-39 up/down/left/right arrow, -33/-34 page up/down,
// -36/-35 pos1/end other key codes (key<0): -45 insert, -144 num lock, -20 caps
// lock, -91 windows key, -93 kontext menu key, -112 to -123 F1 to F12 not
// working: ¹ (251), num lock (-144), caps lock (-20), windows key (-91),
// kontext menu key (-93), F11 (-122)

enum Direction
{
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
};

struct Key
{
    std::string letter;
    int code;
    bool ctrl;
    bool alt;
    bool escape;

    Direction direction = NONE;

    Key(int code)
    {
        this->code = code;
        this->letter = std::string(1, code);
    }

    Key(Direction direction) { this->direction = direction; }

    Key(std::string letter, bool ctrl = false, bool alt = false, bool escape = false)
    {
        if (letter.length() > 1)
            throw MultiLengthLetterException();
        this->letter = letter;
        this->code = static_cast<int>(letter.front());
        this->ctrl = ctrl;
        this->alt = alt;
        this->escape = escape;
    }

    std::string reprSelf()
    {
        std::stringstream ss;

        switch (direction)
        {
        case UP:
            return "[UP]";
        case DOWN:
            return "[DOWN]";
        case LEFT:
            return "[LEFT]";
        case RIGHT:
            return "[RIGHT]";
        default:; // Continue processing
        }

        if (ctrl)
            ss << "Ctrl + ";
        if (alt)
            ss << "Alt + ";
        if (escape)
            ss << "Esc + ";
        ss << letter;

        return ss.str();
    }
};

// https://stackoverflow.com/a/67038432/14868780
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <Windows.h>

Key onKeyPress()
{ // not working: F11 (-122, toggles fullscreen)
    KEY_EVENT_RECORD keyevent;
    INPUT_RECORD irec;
    DWORD events;
    while (true)
    {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &irec, 1, &events);
        if (irec.EventType == KEY_EVENT && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown)
        {
            keyevent = (KEY_EVENT_RECORD&)irec.Event;
            const int ca = (int)keyevent.uChar.AsciiChar;
            const int cv = (int)keyevent.wVirtualKeyCode;
            const int key = ca == 0 ? -cv : ca + (ca > 0 ? 0 : 256);
            switch (key)
            {
            case -16:
                continue; // disable Shift
            case -17:
                continue; // disable Ctrl / AltGr
            case -18:
                continue; // disable Alt / AltGr
            case -220:
                continue; // disable first detection of "^" key (not "^" symbol)
            case -221:
                continue; // disable first detection of "`" key (not "`" symbol)
            case -191:
                continue; // disable AltGr + "#"
            case -52:
                continue; // disable AltGr + "4"
            case -53:
                continue; // disable AltGr + "5"
            case -54:
                continue; // disable AltGr + "6"
            case -12:
                continue; // disable num block 5 with num lock deactivated
            case 13:
                return { 10 }; // enter
            case -46:
                return { 127 }; // delete
            case -49:
                return { 251 }; // ¹
            case 0:
                continue; // null
            case 1:
                return { "a", true }; // disable Ctrl + a (selects all text)
            case 2:
                return { "b", true }; // disable Ctrl + b
            case 3:
                return { "c", true }; // disable Ctrl + c (terminates program)
            case 4:
                return { "d", true }; // disable Ctrl + d
            case 5:
                return { "e", true }; // disable Ctrl + e
            case 6:
                return { "f", true }; // disable Ctrl + f (opens search)
            case 7:
                return { "g", true }; // disable Ctrl + g
            case 8:
                return { "h", true }; // disable Ctrl + h (ascii for backspace)
            case 9:
                return { "i", true }; // disable Ctrl + i (ascii for tab)
            case 10:
                return { "j", true }; // disable Ctrl + j
            case 11:
                return { "k", true }; // disable Ctrl + k
            case 12:
                return { "l", true }; // disable Ctrl + l
            case 13:
                return { "m", true }; // disable Ctrl + m (breaks console, ascii for new
            // line)
            case 14:
                return { "n", true }; // disable Ctrl + n
            case 15:
                return { "o", true }; // disable Ctrl + o
            case 16:
                return { "p", true }; // disable Ctrl + p
            case 17:
                return { "q", true }; // disable Ctrl + q
            case 18:
                return { "r", true }; // disable Ctrl + r
            case 19:
                return { "s", true }; // disable Ctrl + s
            case 20:
                return { "t", true }; // disable Ctrl + t
            case 21:
                return { "u", true }; // disable Ctrl + u
            case 22:
                return { "v", true }; // disable Ctrl + v (inserts clipboard)
            case 23:
                return { "w", true }; // disable Ctrl + w
            case 24:
                return { "x", true }; // disable Ctrl + x
            case 25:
                return { "y", true }; // disable Ctrl + y
            case 26:
                return { "z", true }; // disable Ctrl + z
            default:
                return { key }; // any other ASCII/virtual character
            }
        }
    }
}

#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))

    #include <sys/ioctl.h>
    #include <termios.h>

Key onKeyPress()
{ // not working: superscript 1 (251), num lock (-144), caps
  // lock (-20), windows key (-91), kontext menu key (-93)
    termios term{};
    tcgetattr(0, &term);
    while (true)
    {
        term.c_lflag &= ~(ICANON | ECHO); // turn off line buffering and echoing
        tcsetattr(0, TCSANOW, &term);
        int nbbytes;
        ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN
        while (!nbbytes)
        {
            fflush(stdout);
            ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN
        }
        int key = getchar();
        if (key == 27 || key == 194 || key == 195)
        { // escape, 194/195 is escape for °ß´äöüÄÖÜ
            key = getchar();
            if (key == 91)
            { // [ following escape
                key = getchar(); // get code of next char after \e[
                if (key == 49)
                { // F5-F8
                    key = 62 + getchar(); // 53, 55-57
                    if (key == 115)
                        key++; // F5 code is too low by 1
                    getchar(); // take in following ~ (126), but discard code
                }
                else if (key == 50)
                { // insert or F9-F12
                    key = getchar();
                    if (key == 126)
                    { // insert
                        key = 45;
                    }
                    else
                    { // F9-F12
                        key += 71; // 48, 49, 51, 52
                        if (key < 121)
                            key++; // F11 and F12 are too low by 1
                        getchar(); // take in following ~ (126), but discard code
                    }
                }
                else if (key == 51 || key == 53 || key == 54)
                { // delete, page up/down
                    getchar(); // take in following ~ (126), but discard code
                }
            }
            else if (key == 79)
            { // F1-F4
                key = 32 + getchar(); // 80-83
            }
            key = -key; // use negative numbers for escaped keys
        }
        term.c_lflag |= (ICANON | ECHO); // turn on line buffering and echoing
        tcsetattr(0, TCSANOW, &term);
        switch (key)
        {
        case 127:
            return { 8 }; // backspace
        case -27:
            return { "", false, false, true }; // escape
        case -51:
            return { 127 }; // delete
        case -164:
            return { "ä" }; // ä
        case -182:
            return { "ö" }; // ö
        case -188:
            return { "ü" }; // ü
        case -132:
            return { "Ä" }; // Ä
        case -150:
            return { "Ö" }; // Ö
        case -156:
            return { "Ü" }; // Ü
        case -159:
            return { "ß" }; // ß
        case -181:
            return { "µ" }; // µ
        case -167:
            return { "§" }; // §
        case -176:
            return { "°" }; // °
        case -178:
            return { "²" }; // ²
        case -179:
            return { "³" }; // ³
        case -180:
            return { "´" }; // ´
        case -65:
            return { UP }; // up arrow
        case -66:
            return { DOWN }; // down arrow
        case -68:
            return { LEFT }; // left arrow
        case -67:
            return { RIGHT }; // right arrow
        case -53:
            return { UP }; // page up
        case -54:
            return { DOWN }; // page down
        // case -72:
        //     return -36; // pos1
        // case -70:
        //     return -35; // end
        case 0:
            continue; // null
        case 1:
            return { "a", true }; // disable Ctrl + a
        case 2:
            return { "b", true }; // disable Ctrl + b
        case 3:
            return { "c", true }; // disable Ctrl + c (terminates program)
        case 4:
            return { "d", true }; // disable Ctrl + d
        case 5:
            return { "e", true }; // disable Ctrl + e
        case 6:
            return { "f", true }; // disable Ctrl + f
        case 7:
            return { "g", true }; // disable Ctrl + g
        case 8:
            return { "h", true }; // disable Ctrl + h
        case 9:
            return { "i", true }; // disable Ctrl + i (ascii for tab)
        case 10:
            return { "j", true }; // disable Ctrl + j (ascii for new line)
        case 11:
            return { "k", true }; // disable Ctrl + k
        case 12:
            return { "l", true }; // disable Ctrl + l
        case 13:
            return { "m", true }; // disable Ctrl + m
        case 14:
            return { "n", true }; // disable Ctrl + n
        case 15:
            return { "o", true }; // disable Ctrl + o
        case 16:
            return { "p", true }; // disable Ctrl + p
        case 17:
            return { "q", true }; // disable Ctrl + q
        case 18:
            return { "r", true }; // disable Ctrl + r
        case 19:
            return { "s", true }; // disable Ctrl + s
        case 20:
            return { "t", true }; // disable Ctrl + t
        case 21:
            return { "u", true }; // disable Ctrl + u
        case 22:
            return { "v", true }; // disable Ctrl + v
        case 23:
            return { "w", true }; // disable Ctrl + w
        case 24:
            return { "x", true }; // disable Ctrl + x
        case 25:
            return { "y", true }; // disable Ctrl + y
        case 26:
            continue; // disable Ctrl + z (terminates program)
        default:
            return key; // any other ASCII character
        }
    }
}
#endif // Windows/Linux

std::string getInputChar()
{
    auto key = onKeyPress();
    return key.reprSelf();
}

struct Program
{
    int ctrlCCount = 0;
};

Program program;

[[noreturn]] int main()
{
    signal(SIGINT, [](int) {
        program.ctrlCCount++;
        std::cout << "Press Ctrl-C once more to exit..." << std::endl;

        if (program.ctrlCCount > 1)
            exit(EXIT_SUCCESS);
    });
    auto future = std::async(std::launch::async, getInputChar);

    while (true)
    {
        if (future.wait_for(std::chrono::milliseconds(10)) == std::future_status::ready)
        {
            auto key = future.get();

            // Set a new line. Subtle race condition between the previous line
            // and this. Some lines could be missed. To aleviate, you need an
            // io-only thread. I'll give an example of that as well.
            future = std::async(std::launch::async, getInputChar);

            std::cout << "Key pressed " << key << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
