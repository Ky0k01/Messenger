cmake_minimum_required(VERSION 3.15)
project(Server VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_DIR "C:/Qt/5.15.2/mingw81_64")
set(POSTGRESQL_DIR "C:/Program Files/PostgreSQL/17")
include_directories("${POSTGRESQL_DIR}/include")

file(GLOB TEXT_FILES "readme.txt")
add_custom_target(TextFiles ALL SOURCES ${TEXT_FILES})

add_subdirectory(src)
#add_subdirectory(tests)
