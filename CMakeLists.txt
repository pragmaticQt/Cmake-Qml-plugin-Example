cmake_minimum_required(VERSION 3.0)
project(QaterialPlugin VERSION 1.0 LANGUAGES CXX)
include(cmake/Version.cmake)

find_package(Qt5 REQUIRED COMPONENTS 
  Core
  Gui
  Qml
  Quick
  QuickControls2
  Svg
  Xml
  QuickCompiler
)

set(QT_BIN ${CMAKE_PREFIX_PATH}/bin CACHE STRING "Qt installation bin path")
set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR}/plugins CACHE STRING "Qt Creator qml import paths")

# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)

set(QATERIAL_SOURCE_DIR  ${CMAKE_CURRENT_LIST_DIR}/Qaterial)

set(QATERIAL_DISPLAY_HEADERS
  ${QATERIAL_SOURCE_DIR}/IconDescription.hpp
  ${QATERIAL_SOURCE_DIR}/IconLabelImpl.hpp
  ${QATERIAL_SOURCE_DIR}/IconLabelPositionner.hpp
)
set(QATERIAL_DISPLAY_SRCS
  ${QATERIAL_SOURCE_DIR}/IconDescription.cpp
  ${QATERIAL_SOURCE_DIR}/IconLabelImpl.cpp
  ${QATERIAL_SOURCE_DIR}/IconLabelPositionner.cpp
)

set(QATERIAL_IO_HEADERS
  ${QATERIAL_SOURCE_DIR}/TextFile.hpp
  ${QATERIAL_SOURCE_DIR}/Clipboard.hpp
#  ${QATERIAL_SOURCE_DIR}/FolderTreeModel.hpp
)
set(QATERIAL_IO_SRCS
  ${QATERIAL_SOURCE_DIR}/TextFile.cpp
  ${QATERIAL_SOURCE_DIR}/Clipboard.cpp
#  ${QATERIAL_SOURCE_DIR}/FolderTreeModel.cpp
)

set(QATERIAL_UTILS_HEADERS
#  ${QATERIAL_SOURCE_DIR}/Qaterial.hpp
#  ${QATERIAL_SOURCE_DIR}/Export.hpp
#  ${QATERIAL_SOURCE_DIR}/Property.hpp
  ${QATERIAL_SOURCE_DIR}/Version.hpp
#  ${QATERIAL_SOURCE_DIR}/Utils.hpp
#  ${QATERIAL_SOURCE_DIR}/Logger.hpp
)

set(QATERIAL_UTILS_SRCS
  ${QATERIAL_SOURCE_DIR}/Version.cpp
#  ${QATERIAL_SOURCE_DIR}/Utils.cpp
#  ${QATERIAL_SOURCE_DIR}/Logger.cpp
)
source_group("Header" ${QATERIAL_DISPLAY_HEADERS} ${QATERIAL_IO_HEADERS} ${QATERIAL_UTILS_HEADERS})
source_group("Source" ${QATERIAL_DISPLAY_SRCS} ${QATERIAL_IO_SRCS} ${QATERIAL_UTILS_SRCS})

add_subdirectory(app)
add_subdirectory(plugins)
