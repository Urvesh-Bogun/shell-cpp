cmake_minimum_required(VERSION 3.22)
project(shell-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(shell-cpp-core
	src/parser.cpp
)

target_include_directories(shell-cpp-core PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(shell
	src/main.cpp
)

target_link_libraries(shell PRIVATE
	shell-cpp-core
)

include(CTest)
enable_testing()
add_subdirectory(tests)
