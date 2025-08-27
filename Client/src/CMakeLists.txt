file(GLOB_RECURSE SRC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SRC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SRC_UIS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

set(TS_FILES "${TRANSLATIONS_DIR}/Client_ru_RU.ts")
set(RC_FILE "${RESOURCE_DIR}/Client.rc")

add_executable(${PROJECT_NAME}
    ${SRC_SOURCES}
    ${SRC_HEADERS}
    ${SRC_UIS}
    ${TS_FILES}
    # ${RC_FILE} # Раскомментируйте, если используете .rc
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::WebSockets
    Qt5::UiTools
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:QT_QML_DEBUG>
    $<$<CONFIG:Debug>:QT_DECLARATIVE_DEBUG>
)