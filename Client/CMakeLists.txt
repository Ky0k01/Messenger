cmake_minimum_required(VERSION 3.15)
project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets WebSockets UiTools)

set(SOURCES
    main.cpp
    websocketclient.cpp
    authwindow.cpp
)

set(HEADERS
    websocketclient.h
    authwindow.h
)

set(UIS
    authwindow.ui
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::WebSockets
    Qt5::UiTools
)
