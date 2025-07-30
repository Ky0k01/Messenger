cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Путь к Qt MinGW
set(QT_DIR "C:/Qt/5.15.2/mingw81_64")

## Путь к PostgreSQL
set(POSTGRESQL_DIR "C:/Program Files/PostgreSQL/17")

# Ищем Qt
find_package(Qt5 COMPONENTS Core Network Sql WebSockets REQUIRED)

add_executable(Server main.cpp server.cpp server.h) # Добавь сюда свои исходники

target_link_libraries(Server Qt5::Core Qt5::Network Qt5::Sql Qt5::WebSockets)

# Копирование Qt DLL
add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/Qt5Core.dll"
        "$<TARGET_FILE_DIR:Server>/Qt5Core.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/Qt5Network.dll"
        "$<TARGET_FILE_DIR:Server>/Qt5Network.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/Qt5Sql.dll"
        "$<TARGET_FILE_DIR:Server>/Qt5Sql.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/Qt5WebSockets.dll"
        "$<TARGET_FILE_DIR:Server>/Qt5WebSockets.dll"
)

## Копирование PostgreSQL DLL
add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libpq.dll"
        "$<TARGET_FILE_DIR:Server>/libpq.dll"
)

## Копирование дополнительных DLL, если нужны
add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libintl-9.dll"
        "$<TARGET_FILE_DIR:Server>/libintl-9.dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libiconv-2.dll"
        "$<TARGET_FILE_DIR:Server>/libiconv-2.dll"
)

## Копирование драйверов Qt для PostgreSQL
add_custom_command(TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${QT_DIR}/plugins/sqldrivers"
        "$<TARGET_FILE_DIR:Server>/sqldrivers"
)

## Пути к заголовочным файлам PostgreSQL (если используешь напрямую API)
include_directories("${POSTGRESQL_DIR}/include")
