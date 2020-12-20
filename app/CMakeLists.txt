# posix test
add_executable(posix_test posix_test.cpp)
target_link_libraries(posix_test pthread)

# GPIO example
if (NOT USE_SYSTEM_COMPILER)
	find_package(libGPIO)
	add_executable(libGPIO_example libGPIO_example.cpp)
	target_include_directories(libGPIO_example PUBLIC ${libGPIO_INCLUDE_DIR})
	target_link_libraries(libGPIO_example ${libGPIO_LIBRARY})
endif()

# event_example.cpp
add_executable(event_example event_example.cpp)
target_link_libraries(event_example Event)

# task_example.cpp
add_executable(task_example task_example.cpp)
target_link_libraries(task_example Task)

# display_example.cpp
add_executable(display_example display_example.cpp)
target_link_libraries(display_example DisplayDriver)

# display_task_example.cpp
add_executable(display_task_example display_task_example.cpp)
target_link_libraries(display_task_example DisplayDriverTask)