# Например, используем Qt Test
find_package(Qt5 COMPONENTS Test Core Network Sql WebSockets REQUIRED)

add_executable(${PROJECT_NAME}_tests test_main.cpp)
target_link_libraries(${PROJECT_NAME}_tests Qt5::Test Qt5::Core Qt5::Network Qt5::Sql Qt5::WebSockets)

# Добавь дополнительные исходники, если необходимо (например, server.cpp)
target_sources(${PROJECT_NAME}_tests PRIVATE ../src/server.cpp ../src/server.h)

# Можно добавить кастомные команды копирования dll если нужно запускать тесты отдельно
