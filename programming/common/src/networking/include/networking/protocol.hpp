#pragma once

#include <string>
#include <array>
#include <memory>

namespace Networking
{
    using IPv4Address = std::array<uint8_t, 4>;
    using IPv6Address = std::array<uint8_t, 6>;

    struct Peer
    {
        Peer(std::string name, IPv4Address v4address, IPv6Address v6address);

        std::string m_name;
        IPv4Address m_ip4Address;
        IPv6Address m_ip6Address;
    };

    struct Connection
    {
        int32_t version;
        std::unique_ptr<Peer> peer;
    };
}
