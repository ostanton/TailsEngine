#ifndef TAILS_NETWORK_CLIENT_HPP
#define TAILS_NETWORK_CLIENT_HPP

#include <Tails/Config.hpp>

#include <SFML/Network/TcpSocket.hpp>

namespace tails
{
    class CServer;
    
    /**
     * A "node" in a network.
     */
    class TAILS_API CClient
    {
        friend CServer;
        
    public:
        CClient() = default;
        CClient(const CClient&) = delete;
        CClient(CClient&&) = default;
        CClient& operator=(const CClient&) = delete;
        CClient& operator=(CClient&&) = default;
        virtual ~CClient();
        
        virtual bool connect(sf::IpAddress ip, unsigned short port);
        virtual void disconnect();
        virtual void send(sf::Packet& data);
        virtual void receive(sf::Packet& data);

    protected:
        sf::TcpSocket m_socket;
    };
}

#endif // TAILS_NETWORK_CLIENT_HPP
