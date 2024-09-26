cmake_minimum_required(VERSION 3.10)

project(histfilesimp)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")

set(CMAKE_C_FLAGS_RELEASE "-O2 -s -DNDEBUG -flto")

add_executable(${PROJECT_NAME} main.c main.h)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(CPack)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "eldarielmario@gmail.com")