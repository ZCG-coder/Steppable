#include "colors.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"
#include "fn/basicArithm.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Addition with multiple digits of different length)
std::string a = "6453.55", b = "54329.334";
const auto& addResult1 = add(a, b, 0);
const auto& addResult2 = add(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "60782.884");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()

SECTION(Addition with multiple digits of equal length)
std::string a = "65943.595", b = "54329.334";
const auto& addResult1 = add(a, b, 0);
const auto& addResult2 = add(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "120272.929");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()
TEST_END()
