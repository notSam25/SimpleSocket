project(socketClient)

set(SOURCES
    src/Client.cpp
)

add_executable(client ${SOURCES})
target_include_directories(client PUBLIC include)