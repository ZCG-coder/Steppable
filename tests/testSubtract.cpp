#include "colors.hpp"
#include "invokeCommand.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Subtraction with multiple digits of different length)
std::string a = "54329.334", b = "6345.55";
const auto& subtractResult = invokeCommand({ "subtract", a, b }).output; // Makes sure it works when a and b are inversed.
_.assertIsEqual(subtractResult, "47983.784");
SECTION_END()
