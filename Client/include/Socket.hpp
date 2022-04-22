#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define INVALID_SOCKET (int)(~0)
#define SOCKET_ERROR (-1)

class Socket    {
public:
    Socket();
    enum SocketError  {
        SUCESS = 1,
        ADDRESS_INVALID = 0,
        ADDRESS_ERROR = -1
    };

    void setPort(int port);
    int setAddress(const std::string &address);
    int socketID;
    sockaddr_in socketAddress;
};

class UDPClient : public Socket {
public:
    UDPClient(int port, const std::string &IPAddress);
    void sendMessage(const std::string& message);
    void reciveMessage();
};

Socket::Socket() : socketID(), socketAddress()  {
    socketID = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketID == INVALID_SOCKET) {
        throw std::runtime_error("[!] Failed to create socket");
    }
    socketAddress.sin_family = AF_INET;
}

void Socket::setPort(int port)  {
    this->socketAddress.sin_port = htons(port);
}

int Socket::setAddress(const std::string &address)  {
    return inet_pton(AF_INET, address.c_str(), &this->socketAddress.sin_addr);
}

UDPClient::UDPClient(int port, const std::string& IPAddress)    {
    setPort(port);
    SocketError SocketState(static_cast<SocketError>(setAddress(IPAddress)));
    switch(SocketState) {
        case SocketError::SUCESS:
            std::cout << "[*] Created socket client" << std::endl;
        break;
        case SocketError::ADDRESS_INVALID:
            throw std::runtime_error("[!] Socket address invalid");
        break;
        case SocketError::ADDRESS_ERROR:
            throw std::runtime_error("[!] Socket address family error");
        break;
        default:
            throw std::runtime_error("[!] Unhandled socket error");
        break;
    }
}

void UDPClient::sendMessage(const std::string& message)    {
    std::cout << "[*] Sending packet" << std::endl;
    sendto(socketID, message.c_str(), message.length(), 0, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));
}

void UDPClient::reciveMessage()    {
    sockaddr_in client;
    socklen_t slen = sizeof(client);
    char client_ip[INET_ADDRSTRLEN], buffer[512];

    while(true)
    {
        ssize_t recvLength = recvfrom(socketID, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&client), &slen);
        if (recvLength == SOCKET_ERROR)
            std::cout << "[!] Error reciving data" << std::endl;
        
        std::cout << "[*] Received packet from " << inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN) << ':' << ntohs(client.sin_port) << std::endl;
        std::cout << "[*] Data recived: " << buffer << std::endl;
    }
}