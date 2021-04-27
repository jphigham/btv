cmake_minimum_required(VERSION 3.1.0)

project(btv LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5.15.2)

if (UNIX)
  set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/${QT_VERSION}/gcc_64)
elseif(WIN32)
  set(CMAKE_PREFIX_PATH C:/Qt/${QT_VERSION}/mingw81_64)
endif()

find_package(Qt5 ${QT_VERSION} COMPONENTS Core Gui Widgets REQUIRED)

add_executable(btv
    main.cpp
    DoubleSlider.cpp
    Node.cpp
    NodeWidget.cpp
    TreeWidget.cpp
    TreeWindow.cpp
)

target_link_libraries(btv Qt::Core)
target_link_libraries(btv Qt::Gui)
target_link_libraries(btv Qt::Widgets)
