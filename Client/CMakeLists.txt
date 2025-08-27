cmake_minimum_required(VERSION 3.15)
project(Client VERSION 0.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

set(TRANSLATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets WebSockets UiTools LinguistTools Test)

add_subdirectory(src)
add_subdirectory(tests)
