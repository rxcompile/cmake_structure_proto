#pragma once

#include <array>

namespace Network
{
    struct Connection
    {
        int32_t version;
        std::array<int32_t, 256> someData;
    };
}
