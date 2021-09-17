cmake_minimum_required(VERSION 3.5)

project(MainProject)

if(WIN32)
    set (CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019/")
endif()

if(APPLE)
    set (CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.15.2/clang_64/)
    add_compile_options(-arch x86_64)
endif()

add_subdirectory(XCppfilt)
add_subdirectory(XCapstone)
add_subdirectory(XArchive)
add_subdirectory(gui_source)