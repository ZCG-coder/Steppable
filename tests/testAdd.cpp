#include "colors.hpp"
#include "invokeCommand.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Addition with multiple digits of different length)
std::string a = "6453.55", b = "54329.334";
const auto& addResult1 = invokeCommand({ "add", a, b }).output;
const auto& addResult2 = invokeCommand({ "add", b, a }).output; // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "60782.884");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()

SECTION(Addition with multiple digits of equal length)
std::string a = "65943.595", b = "54329.334";
const auto& addResult1 = invokeCommand({ "add", a, b }).output;
const auto& addResult2 = invokeCommand({ "add", b, a }).output; // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "120272.929");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()
TEST_END()
