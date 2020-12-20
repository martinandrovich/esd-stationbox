
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/CrossCompiling
message("-- Executing <zybo-toolchain.cmake>")

# define toolchain path
set(TOOLCHAIN_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/plnx-2017.4-arm-6.2.1/linux-i386/gcc-arm-linux-gnueabi/bin)

# cross compiler config (Linux, arm)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# define compilers
set(CMAKE_AR           ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER   ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER       ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY      ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB       ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE         ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-size${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP        ${TOOLCHAIN_BINARY_DIR}/arm-linux-gnueabihf-strip${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)