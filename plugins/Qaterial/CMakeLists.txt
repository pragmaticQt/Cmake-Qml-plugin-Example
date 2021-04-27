
qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/plugin.qrc)

add_library( qaterialplugin SHARED

    ${CMAKE_CURRENT_LIST_DIR}/qaterialplugin.h
#    ${CMAKE_CURRENT_LIST_DIR}/IconDescription.hpp

    ${CMAKE_CURRENT_LIST_DIR}/qaterialplugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../Qaterial/IconDescription.cpp

    # It's not important to include 'qmldir' or 'plugin.qmltypes' here,
    # but it will make IDEs (such as Qt Creator) to include them in project tree
    ${CMAKE_CURRENT_LIST_DIR}/qmldir
#    ${CMAKE_CURRENT_LIST_DIR}/plugin.qmltypes

    ${PLUGIN_RESOURCES}     # Plugin resources file
)
target_compile_definitions(qaterialplugin PUBLIC -DQATERIAL_SHARED)
target_include_directories(qaterialplugin PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../..)
target_compile_features(
    qaterialplugin
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

target_link_libraries( qaterialplugin PUBLIC
  Qt::Core
  Qt::Gui
  Qt::Svg
  Qt::Xml
  Qt::Qml
  Qt::Quick
  Qt::QuickControls2
)

# During plugin searching Qt will be looking for 'qmldir' file
# So we should place it next to our plugin lib.
add_custom_command(
    TARGET qaterialplugin
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/qmldir
        $<TARGET_FILE_DIR:qaterialplugin>/qmldir
    COMMAND
        cd $<TARGET_FILE_DIR:qaterialplugin>/.. &&
        ${QT_BIN}/qmlplugindump.exe -nonrelocatable Qaterial 1.0 . > Qaterial/plugin.qmltypes

)

