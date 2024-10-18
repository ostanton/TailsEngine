#ifndef TAILS_NETWORK_SERVER_HPP
#define TAILS_NETWORK_SERVER_HPP

#include <Tails/Config.hpp>
#include <Tails/Client.hpp>

#include <SFML/Network/TcpListener.hpp>

#include <vector>

namespace tails
{
    /**
     * A specialised "node" that lets other nodes connect to it. A listener server
     */
    class TAILS_API CServer final : public CClient
    {
    public:
        CServer() = default;
        explicit CServer(unsigned short port, sf::IpAddress ip = sf::IpAddress::Any);
        
        bool start(unsigned short port, sf::IpAddress ip = sf::IpAddress::Any);
        void stop();
        void acceptClient();

    private:
        bool connect(sf::IpAddress ip, unsigned short port) override;
        void disconnect() override;
        void send(sf::Packet& data) override;
        
        sf::TcpListener m_listener;
        std::vector<CClient> m_clients;
    };
}

#endif // TAILS_NETWORK_SERVER_HPP
