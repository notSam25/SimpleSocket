#include <string>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
typedef int SOCKET;
// These could also be enums
const int socket_bind_err = 3;
const int socket_accept_err = 4;
const int connection_err = 5;
const int message_send_err = 6;
const int receive_err = 7;

class Socket
{
public:
    enum class SocketType
    {
        TYPE_STREAM = SOCK_STREAM,
        TYPE_DGRAM = SOCK_DGRAM
    };

protected:
    explicit Socket(SocketType socket_type);
    ~Socket();
    SOCKET m_socket;
    sockaddr_in m_addr;
    void set_port(u_short port);
    int set_address(const std::string &ip_address);

private:
};


class UDPClient : public Socket
{
public:
    UDPClient(u_short port = 8000, const std::string &ip_address = "127.0.0.1");
    ssize_t send_message(const std::string &message);
    void Listen();
};

Socket::Socket(const SocketType socket_type) : m_socket(), m_addr()
{
    // Create the socket handle
    m_socket = socket(AF_INET, static_cast<int>(socket_type), 0);
    if (m_socket == INVALID_SOCKET)
    {
        throw std::runtime_error("Could not create socket");
    }

    m_addr.sin_family = AF_INET;
}

void Socket::set_port(u_short port)
{
    m_addr.sin_port = htons(port);
}

int Socket::set_address(const std::string &ip_address)
{
    return inet_pton(AF_INET, ip_address.c_str(), &m_addr.sin_addr);
}
Socket::~Socket() = default;

UDPClient::UDPClient(u_short port, const std::string &ip_address) : Socket(SocketType::TYPE_DGRAM)
{
    set_address(ip_address);
    set_port(port);
    std::cout << "UDP Client created." << std::endl;
};

ssize_t UDPClient::send_message(const std::string &message)
{
    size_t message_length = message.length();
    return sendto(m_socket, message.c_str(), message_length, 0, reinterpret_cast<sockaddr *>(&m_addr), sizeof(m_addr));
};

void UDPClient::Listen()    {
    sockaddr_in client;
    char client_ip[INET_ADDRSTRLEN];
    socklen_t slen = sizeof(client);
    char message_buffer[512];
    std::cout << "Waiting for data..." << std::endl;

    while(true)
    {
        ssize_t recv_len = recvfrom(m_socket, message_buffer, sizeof(message_buffer), 0, reinterpret_cast<sockaddr*>(&client), &slen);
        if (recv_len == SOCKET_ERROR)
        {
            std::cout << "Receive Data error." << std::endl;
        }
        std::cout << "Received packet from " << inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN) << ':' << ntohs(client.sin_port) << std::endl;
        std::cout << message_buffer << std::endl;
    }
}