cmake_minimum_required(VERSION 3.9)

project(ShowImages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)

add_executable(ShowImages
  processimage.cpp
  main.cpp
  loadfilenamesbckgrnd.cpp
  mainwindow.ui
  mainwindow.cpp
)

target_link_libraries(ShowImages Qt5::Core Qt5::Gui Qt5::Widgets)
