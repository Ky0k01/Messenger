cmake_minimum_required(VERSION 3.15)
project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets WebSockets UiTools LinguistTools)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(UI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(TRANSLATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB HEADERS "${INCLUDE_DIR}/*.h")
file(GLOB UIS "${UI_DIR}/*.ui")
set(TS_FILES "${TRANSLATIONS_DIR}/Client_ru_RU.ts")
#set(RC_FILE "${RESOURCE_DIR}/TestingProgram.rc")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::WebSockets Qt5::UiTools)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${UI_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# Настройки сборки
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:QT_QML_DEBUG>
    $<$<CONFIG:Debug>:QT_DECLARATIVE_DEBUG>
)
