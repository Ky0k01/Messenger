find_package(Qt5 COMPONENTS Core Network Sql WebSockets REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Sql Qt5::WebSockets)

# Копирование Qt DLL
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
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

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/libwinpthread-1.dll"
        "$<TARGET_FILE_DIR:Server>/libwinpthread-1.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/libstdc++-6.dll"
        "$<TARGET_FILE_DIR:Server>/libstdc++-6.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_DIR}/bin/libgcc_s_seh-1.dll"
        "$<TARGET_FILE_DIR:Server>/libgcc_s_seh-1.dll"
)

# Копирование PostgreSQL DLL
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libpq.dll"
        "$<TARGET_FILE_DIR:Server>/libpq.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libintl-9.dll"
        "$<TARGET_FILE_DIR:Server>/libintl-9.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libiconv-2.dll"
        "$<TARGET_FILE_DIR:Server>/libiconv-2.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libcrypto-3-x64.dll"
        "$<TARGET_FILE_DIR:Server>/libcrypto-3-x64.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POSTGRESQL_DIR}/bin/libssl-3-x64.dll"
        "$<TARGET_FILE_DIR:Server>/libssl-3-x64.dll"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${QT_DIR}/plugins/sqldrivers"
        "$<TARGET_FILE_DIR:Server>/sqldrivers"
)
