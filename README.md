## SimpleSocket
> A simple Client/Sever exmaple for a UDP Socket connection.

## About
    Sever:
    The sever is made for nodeJS, it makes a UDP Server with DGRAM.

    Client:
    The client contains a single header for the UDP Client, the Socket.cpp takes input via command line for the connection setup.
    
## Build
    Server:
    ```
    npm init
    npm install dgram
    npm start
    ```
    Client:
    ```
    cmake CMakeLists.txt
    make
    ```