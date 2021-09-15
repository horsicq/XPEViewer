cmake_minimum_required(VERSION 3.5)

project(MainProject)

set (CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019/")

add_subdirectory(XCppfilt)
add_subdirectory(XCapstone)
add_subdirectory(XArchive)
add_subdirectory(gui_source)