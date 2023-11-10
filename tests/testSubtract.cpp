#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Subtraction with multiple digits of different length)
std::string a = "54329.334", b = "6345.55";
const auto& subtractResult = subtract(a, b, 0);

_.assertIsEqual(subtractResult, "47983.784");
SECTION_END()

TEST_END()
