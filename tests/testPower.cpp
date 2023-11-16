#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Power)
const std::string_view& number = "47", raiseTo = "10";
const auto& result = power(number, raiseTo, 0);

_.assertIsEqual(result, "52599132235830049");
SECTION_END()
TEST_END()
