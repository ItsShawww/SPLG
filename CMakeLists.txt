cmake_minimum_required(VERSION "3.19")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")



add_subdirectory(thirdparty/raylib)

project(sim)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
add_executable(sim ${SOURCES})
target_include_directories(sim PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)
target_link_libraries(sim PRIVATE 
    raylib
)
