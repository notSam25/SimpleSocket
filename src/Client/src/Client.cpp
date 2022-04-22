#include <Socket.hpp>

int main()  {

    UDPClient client(2222, "127.0.0.1");
    client.Send("This message is going to the nodeJS server!");
    client.Recive();
    return 0;
}