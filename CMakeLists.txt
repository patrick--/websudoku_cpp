
cmake_minimum_required(VERSION 3.1)

project(websudoku_cpp)

set(CMAKE_CXX_STANDARD 17)

set (SOURCES
	src/main.cpp
	src/websudoku.cpp
)


add_executable(websudoku_cpp ${SOURCES})

target_include_directories(websudoku_cpp
	PRIVATE
		${PROJECT_SOURCE_DIR}/external/cpp-httplib)