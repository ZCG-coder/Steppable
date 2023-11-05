#include "colors.hpp"
#include "invokeCommand.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Multiplication without carry)
std::string a = "2", b = "4";
const auto& multiplyResult1 = invokeCommand({ "multiply", a, b }).output;
const auto& multiplyResult2 = invokeCommand({ "multiply", b, a }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(multiplyResult1, "8");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with one carry)
std::string a = "56", b = "45";
const auto& multiplyResult1 = invokeCommand({ "multiply", a, b }).output;
const auto& multiplyResult2 =
    invokeCommand({ "multiply", b, a }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(multiplyResult1, "2520");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with two carries)
std::string a = "12", b = "9";
const auto& multiplyResult1 = invokeCommand({ "multiply", a, b }).output;
const auto& multiplyResult2 =
    invokeCommand({ "multiply", b, a }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(multiplyResult1, "108");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()
TEST_END()
