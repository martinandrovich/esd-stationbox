cmake_minimum_required(VERSION 3.11...3.18)

# set toolchain (sytem or ARM)
option(USE_SYSTEM_COMPILER "Use system compiler instead of toolchain compiler." OFF)
if (NOT USE_SYSTEM_COMPILER)
	message("-- Using TOOLCHAIN COMPILER!")
	set(CMAKE_TOOLCHAIN_FILE cmake/zybo-toolchain.cmake)
else()
	message("-- Using SYSTEM COMPILER!")
endif()

# initialize the project (checks compilers etc.)
project(
	esd-zybo-project
	VERSION 1.0
	DESCRIPTION "Zybo related libraries and apps for the Stationbox project of the ESD course."
	LANGUAGES CXX
)

# helper CMake files directory
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# CMake and C++ settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add external libraries (must come before project dirs)
add_subdirectory(extern/serialib)

# add project directories
add_subdirectory(src) # library source code
add_subdirectory(app) # applications
