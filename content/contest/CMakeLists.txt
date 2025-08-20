cmake_minimum_required(VERSION 3.24)
project(main)

set(CMAKE_CXX_STANDARD 20)

file(GLOB sources *.cpp)

add_compile_definitions(LOCAL)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -fsanitize=address,undefined")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

foreach(src ${sources})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
endforeach()
