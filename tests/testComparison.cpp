#include "colors.hpp"
#include "invokeCommand.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Comparison at integer)
std::string a = "6453.55", b = "54329.334";
const auto& compareResult1 = invokeCommand({ "comparison", a, b }).output;
const auto& compareResult2 =
    invokeCommand({ "comparison", b, a }).output; // Makes sure it works when a and b are reordered.
_.assertIsEqual(compareResult1, "0");
_.assertIsEqual(compareResult2, "1");
SECTION_END()

SECTION(Comparison by digit without decimal point)
std::string a = "659", b = "543";
const auto& compareResult1 = invokeCommand({ "comparison", a, b }).output;
const auto& compareResult2 =
    invokeCommand({ "comparison", b, a }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(compareResult1, "1");
_.assertIsEqual(compareResult2, "0");
SECTION_END()

SECTION(Comparison by digit with decimal point)
std::string a = "659.2234", b = "659.5242";
const auto& compareResult1 = invokeCommand({ "comparison", a, b }).output;
const auto& compareResult2 =
    invokeCommand({ "comparison", b, a }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(compareResult1, "0");
_.assertIsEqual(compareResult2, "1");
SECTION_END()
TEST_END()
