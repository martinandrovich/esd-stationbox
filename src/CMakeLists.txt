# Event.cpp
add_library(Event Event.cpp)
target_include_directories(Event PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Task.cpp
add_library(Task Task.cpp)
target_include_directories(Task PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Task Event pthread)

# DisplayDriver.cpp
add_library(DisplayDriver DisplayDriver.cpp)
target_include_directories(DisplayDriver PUBLIC ${PROJECT_SOURCE_DIR}/include ${serialib_INCLUDE_DIR})
target_link_libraries(DisplayDriver serialib)

# DisplayDriverTask.cpp
add_library(DisplayDriverTask DisplayDriverTask.cpp)
target_include_directories(DisplayDriverTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DisplayDriverTask Task DisplayDriver)