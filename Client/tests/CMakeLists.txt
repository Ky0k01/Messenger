file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME}_tests
    ${TEST_SOURCES}
    ${TEST_HEADERS}
)

target_link_libraries(${PROJECT_NAME}_tests
    Qt5::Test
    Qt5::Core
    Qt5::Widgets
    Qt5::WebSockets
    Qt5::UiTools
)
target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)
