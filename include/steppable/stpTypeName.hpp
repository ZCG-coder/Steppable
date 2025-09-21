#pragma once

#include <map>
#include <string>

enum STP_TypeID
{
    STP_TypeID_NULL = 0,
    STP_TypeID_NUMBER = 1,
    STP_TypeID_MATRIX_2D = 2,
    STP_TypeID_STRING = 3,
    STP_TypeID_FUNC = 4,
    STP_TypeID_SYMBOL = 5,
};

inline const std::map<STP_TypeID, std::string> STP_typeNames = {
    { STP_TypeID_NUMBER, "Number" }, { STP_TypeID_MATRIX_2D, "Mat2D" }, { STP_TypeID_STRING, "Str" },
    { STP_TypeID_FUNC, "Func" },     { STP_TypeID_NULL, "Null" },       { STP_TypeID_SYMBOL, "Symbol" },
};
