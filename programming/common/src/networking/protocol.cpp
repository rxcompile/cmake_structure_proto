#include "networking/protocol.hpp"

namespace Networking
{
    Peer::Peer(std::string name, IPv4Address v4address, IPv6Address v6address)
        : m_name(std::move(name))
        , m_ip4Address(std::move(v4address))
        , m_ip6Address(std::move(v6address))
    {
    };
}