#### TERRAIN CMAKE FILE
cmake_minimum_required(VERSION 3.1)
project(terrain)

## C++17 COMPILER SUPPORT
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

## PROJECT FILES
include_directories(${CMAKE_SOURCE_DIR}/inc)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/chunk)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/sys)



## EXECUTABLE
add_executable(${PROJECT_NAME} ${PROJECT_SRC})

## Copy game assets over
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/asset/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/asset/)

## PACKAGES
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
  PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

  target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} stdc++fs)
else()
  message(STATUS "ERROR: pkg-config is not installed on this system.")
endif()


## FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -pthread -g -Wall -DDEBUG_BUILD")
