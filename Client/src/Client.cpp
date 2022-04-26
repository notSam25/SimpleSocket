#include <Socket.hpp>
#include <Common.hpp>

using DebugClass = Common::Debug;
DebugClass Debug;

int main()  {

    Common::PrintSystemInformation();
    if(strcmp(Common::GetOperatingSystemName(), "linux") == 1)  {
        Debug.LogData(Debug.LogType::Error, "Only linux is supported");
        getchar();
        exit(-1);
    }
    
    std::string tIPAdress;
    int tPort;
    Debug.LogData(Debug.LogType::Info, "Input desired connection address");
    std::cin >> tIPAdress;
    Debug.LogData(Debug.LogType::Info, "Input desired connection port");
    std::cin >> tPort;
    std::cout << "[#] ";
    UDPClient client(tPort, tIPAdress);
    client.sendMessage("This message is going to the nodeJS server!");
    client.reciveMessage();

    return 0;
}