#pragma once

#include <cstdint>

namespace steppable
{
    /**
     * @enum RoundingMode
     * @brief Specifies how Steppable should round the number in operations.
     */
    enum class RoundingMode : std::uint8_t
    {
        /// @brief Use the higher precision whenever possible.
        USE_MAXIMUM_PREC = 0xFF,

        /// @brief Use the lower precision whenever possible.
        USE_MINIMUM_PREC = 0x01,

        /// @brief Use the current precision.
        USE_CURRENT_PREC = 0x02,

        /// @brief Use the other number's precision.
        USE_OTHER_PREC = 0x03,

        /// @brief Do not append any decimal places.
        DISCARD_ALL_DECIMALS = 0x00
    };

    enum class Rounding : std::uint8_t
    {
        ROUND_DOWN = 0x00, ///< Rounds the number down.
        ROUND_UP = 0x01, ///< Rounds the number up.
        ROUND_OFF = 0x02, ///< Rounds the number off.
    };
} // namespace steppable
