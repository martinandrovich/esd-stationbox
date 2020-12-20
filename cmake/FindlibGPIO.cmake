message("-- Executing <FindlibPGIO.cmake>")

set(libGPIO_LIBRARY ${PROJECT_SOURCE_DIR}/lib/libGPIO.so)
set(libGPIO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libGPIO REQUIRED_VARS libGPIO_LIBRARY libGPIO_INCLUDE_DIR)
mark_as_advanced(libGPIO_INCLUDE_DIR libGPIO_LIBRARY)