#include <Tails/Network/Client.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

namespace tails
{
    CClient::~CClient()
    {
        disconnect();
    }

    bool CClient::connect(sf::IpAddress ip, unsigned short port)
    {
        if (m_socket.connect(ip, port) != sf::Socket::Status::Done)
        {
            debug::print("Failed to connect to IP ", ip, " at port ", port);
            return false;
        }
        
        debug::print("Successfully connected to IP ", ip, " at port ", port);
        return true;
    }

    void CClient::disconnect()
    {
        debug::print("Client disconnecting...");
        m_socket.disconnect();
    }

    void CClient::send(sf::Packet& data)
    {
        if (m_socket.send(data) != sf::Socket::Status::Done)
        {
            debug::print("Failed to send packet of size ", data.getDataSize(), " to server");
            return;
        }

        debug::print("Sent packet of size ", data.getDataSize(), " to server");
    }

    void CClient::receive(sf::Packet& data)
    {
        if (m_socket.receive(data) != sf::Socket::Status::Done)
        {
            debug::print("Failed to receive packet from server");
            return;
        }

        debug::print("Received packet of size ", data.getDataSize(), " from server");
    }
}
