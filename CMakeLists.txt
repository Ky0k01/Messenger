cmake_minimum_required(VERSION 3.16)
project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Путь к установке Qt для MinGW
set(Qt5_DIR "D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")  # Обновите путь к своей версии Qt

find_package(Qt5 REQUIRED COMPONENTS Core WebSockets Sql Network)

add_executable(Server
    main.cpp
    server.h
    server.cpp
)

target_link_libraries(Server
    Qt5::Core
    Qt5::WebSockets
    Qt5::Sql
    Qt5::Network
)

