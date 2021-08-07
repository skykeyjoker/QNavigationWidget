cmake_minimum_required (VERSION 3.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXXSTANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_TOOLCHAIN_FILE "D:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project ("QNavigationWidgetTest")

find_package(Qt5 COMPONENTS Core Gui Widgets)
include_directories(../)

add_executable (QNavigationWidgetTest "../QNavigationWidget.cpp" "../QNavigationWidget.h" "main.cpp" "../QNavigationTab.h" "../QNavigationTab.cpp" "QNavigationWidgetTest.cpp" "QNavigationWidgetTest.h")

target_link_libraries(QNavigationWidgetTest Qt5::Widgets Qt5::Gui Qt5::Core)

