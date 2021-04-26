cmake_minimum_required(VERSION 3.0)
project(app VERSION 1.0 LANGUAGES CXX)

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

add_subdirectory(app)
add_subdirectory(plugins)
