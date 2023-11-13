#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(isZeroString)
const std::string &string1 = "0", string2 = "3", string3 = "a";
const bool isZeroString1 = isZeroString(string1), isZeroString2 = isZeroString(string2),
           isZeroString3 = isZeroString(string3);

_.assertTrue(isZeroString1);
_.assertFalse(isZeroString2);
_.assertFalse(isZeroString3);
SECTION_END()

SECTION(isNumber)
const std::string &string1 = "123", string2 = "113241.43152", string3 = "a13489b";
const bool isNumber1 = isNumber(string1), isNumber2 = isNumber(string2), isNumber3 = isNumber(string3);

_.assertTrue(isNumber1);
_.assertTrue(isNumber2);
_.assertFalse(isNumber3);
SECTION_END()

SECTION(split)
const std::string string1 = "1,2,3", string2 = "1", string3 = ",,,", string4 = "";
const auto &out1 = split(string1, ','), out2 = split(string2, ','), out3 = split(string3, ','),
           out4 = split(string4, ',');

_.assertIsEqual(out1.size(), 3);
_.assertIsEqual(out2.size(), 1);
_.assertIsEqual(out3.size(), 3);
_.assertIsEqual(out4.size(), 0);
SECTION_END()

SECTION(splitNumber without padInteger or padDecimal)
const std::string &number1 = "1.24", number2 = "2";
const auto& out = splitNumber(number1, number2, false, false);

_.assertIsEqual(out[0], "1");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], "2");
_.assertIsEqual(out[3], "");
SECTION_END()

SECTION(splitNumber with padInteger except padDecimal)
const std::string &number1 = "11.24", number2 = "2";
const auto& out = splitNumber(number1, number2, true, false);

_.assertIsEqual(out[0], "11");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], " 2");
_.assertIsEqual(out[3], "");
SECTION_END()

SECTION(splitNumber with padInteger and padDecimal)
const std::string &number1 = "11.24", number2 = "2.2";
const auto& out = splitNumber(number1, number2, true, true);

_.assertIsEqual(out[0], "11");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], " 2");
_.assertIsEqual(out[3], "20");
SECTION_END()

SECTION(lReplace)
const std::string &string1 = "aaaaaab", string2 = "bbb";
const auto &out1 = lReplace(string1, 'a'), out2 = lReplace(string2, 'a'), out3 = lReplace(string1, 'a', 'c'),
           out4 = lReplace(string2, 'a', 'c');

_.assertIsEqual(out1, "b");
_.assertIsEqual(out2, "bbb");
_.assertIsEqual(out3, "ccccccb");
_.assertIsEqual(out4, "bbb");
SECTION_END()

SECTION(rReplace)
const std::string &string1 = "baaaaaa", string2 = "bbb";
const auto &out1 = rReplace(string1, 'a'), out2 = rReplace(string2, 'a'), out3 = rReplace(string1, 'a', 'c'),
           out4 = rReplace(string2, 'a', 'c');

_.assertIsEqual(out1, "b");
_.assertIsEqual(out2, "bbb");
_.assertIsEqual(out3, "bcccccc");
_.assertIsEqual(out4, "bbb");
SECTION_END()

SECTION(bothEndsReplace)
const std::string &string1 = "baaaabb", string2 = "aaa";
const auto &out1 = bothEndsReplace(string1, 'b'), out2 = bothEndsReplace(string2, 'b'),
           out3 = bothEndsReplace(string1, 'b', 'c'), out4 = bothEndsReplace(string2, 'b', 'c');

_.assertIsEqual(out1, "aaaa");
_.assertIsEqual(out2, "aaa");
_.assertIsEqual(out3, "caaaacc");
_.assertIsEqual(out4, "aaa");
SECTION_END()

SECTION(removeLeadingZeros)
const std::vector<int>& vector = { 0, 0, 142, 0, 142, 0, 0 };
const auto& out = removeLeadingZeros(vector);

_.assertIsEqual(out.size(), 7);
_.assertIsEqual(out[0], out[1]);
_.assertIsEqual(out[0], -2);
SECTION_END()

SECTION(MAKE_WIDER)
const std::string& in = "abcdefg";
const auto& out = makeWider(in);

_.assertIsEqual(out, "a  b  c  d  e  f  g");
SECTION_END()

TEST_END()
