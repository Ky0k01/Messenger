cmake_minimum_required(VERSION 3.12)
project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets WebSockets UiTools)

set(SOURCES
    main.cpp
    authorisationwindow.cpp
    websocketclient.cpp
    mainwindow.cpp
)

set(HEADERS
    authorisationwindow.h
    websocketclient.h
    mainwindow.h
)

# List your .ui files here
set(UIS
    authorisationwindow.ui
    mainwindow.ui
)

# This will generate moc and ui headers automatically
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
