cmake_minimum_required(VERSION 3.17)
project(Dictionary_JetBrains)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.12.10\\mingw73_64\\lib\\cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(Dictionary_JetBrains main.cpp
        MainWindow.cpp MainWindow.h MainWindow.ui
        Dictionary.cpp Dictionary.h
        Range.cpp Range.h
        SearchProducer.h SearchProducer.cpp)

target_link_libraries(Dictionary_JetBrains PRIVATE Qt5::Widgets)
