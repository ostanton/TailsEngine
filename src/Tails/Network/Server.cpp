#include <Tails/Network/Server.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>

namespace tails
{
    CServer::CServer(unsigned short port, sf::IpAddress ip)
    {
        start(port, ip);
    }

    bool CServer::start(unsigned short port, sf::IpAddress ip)
    {
        if (m_listener.listen(port, ip) != sf::Socket::Status::Done)
        {
            CDebug::print("Failed to listen to port ", port, " at IP ", ip);
            return false;
        }

        CDebug::print("Listening to port ", port, " at IP ", ip);

        //if (m_socket.connect(ip, port) != sf::Socket::Status::Done)
        //{
        //    CDebug::print("Failed to connected to local server");
        //    return false;
        //}
        
        return true;
    }

    void CServer::stop()
    {
        m_listener.close();
    }

    void CServer::acceptClient()
    {
        while (true)
        {
            CDebug::print("Accepting clients...");
            if (CClient client; m_listener.accept(client.m_socket) == sf::Socket::Status::Done)
            {
                CDebug::print("Accepted client from port ", client.m_socket.getRemotePort());
                m_clients.emplace_back(std::move(client));
                break;
            }
        }
    }

    bool CServer::connect(sf::IpAddress ip, unsigned short port)
    {
        CDebug::print("Server cannot connect to another server");
        return false;
    }

    void CServer::disconnect()
    {
        CDebug::print("Server cannot disconnect from another server");
    }

    void CServer::send(sf::Packet& data)
    {
        for (auto& client : m_clients)
        {
            client.send(data);
        }
    }
}
