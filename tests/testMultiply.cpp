#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Multiplication without carry)
std::string a = "2", b = "4";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(multiplyResult1, "8");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with one carry)
std::string a = "56", b = "45";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(multiplyResult1, "2520");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with two carries)
std::string a = "12", b = "9";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are inversed.
_.assertIsEqual(multiplyResult1, "108");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()
TEST_END()
