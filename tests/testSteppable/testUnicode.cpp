#include "symbols.hpp"
#include "testing.hpp"

TEST_START()

SECTION(Test string width)

_.assertIsEqual(steppable::prettyPrint::getStringWidth(R"(Lorem ipsum
dolor                                sit amet!!!
consectetuer adipiscing elit. 中文中文中文中文中文)"),
                static_cast<size_t>(48));
_.assertIsEqual(steppable::prettyPrint::getStringWidth("RIGHT\nALIGNED!!!"), static_cast<size_t>(10));
_.assertIsEqual(steppable::prettyPrint::getStringHeight(R"()"), static_cast<size_t>(0));
_.assertIsEqual(steppable::prettyPrint::getStringHeight(R"(A

B)"),
                static_cast<size_t>(3));

SECTION_END()

TEST_END()