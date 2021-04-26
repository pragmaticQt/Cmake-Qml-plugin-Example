
qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/plugin.qrc)

add_library(
    myplugin
    SHARED

    ${CMAKE_CURRENT_LIST_DIR}/myplugin.h
    ${CMAKE_CURRENT_LIST_DIR}/myquickitem.h

    ${CMAKE_CURRENT_LIST_DIR}/myplugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/myquickitem.cpp

    # It's not important to include 'qmldir' or 'plugin.qmltypes' here,
    # but it will make IDEs (such as Qt Creator) to include them in project tree
    ${CMAKE_CURRENT_LIST_DIR}/qmldir
#    ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes

    ${PLUGIN_RESOURCES}     # Plugin resources file
)


target_compile_features(
    myplugin
    PRIVATE
        cxx_auto_type
        cxx_generic_lambdas
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

target_link_libraries(
    myplugin
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

# During plugin searching Qt will be looking for 'qmldir' file
# So we should place it next to our plugin lib.
add_custom_command(
    TARGET myplugin
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
        $<TARGET_FILE_DIR:myplugin>/qmldir
    COMMAND
        cd $<TARGET_FILE_DIR:myplugin>/../../.. &&
        ${QT_BIN}/qmlplugindump.exe -nonrelocatable my.plugin.example 1.0 . > my/plugin/example/plugin.qmltypes

)

