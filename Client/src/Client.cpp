#include <Socket.hpp>

int main()  {
    std::string tIPAdress;
    int tPort;

    std::cout << "[#] Input desired connection address\n> ";
    std::cin >> tIPAdress;
    std::cout << "[#] Input desired connection port\n> ";
    std::cin >> tPort;

    UDPClient client(tPort, tIPAdress);
    client.sendMessage("This message is going to the nodeJS server!");
    client.reciveMessage();

    return 0;
}