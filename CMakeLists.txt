cmake_minimum_required(VERSION 3.10)

project(histfilesimp)

if (WIN32)
    message(FATAL_ERROR "This project is not supported on Windows")
elseif(APPLE)
    message(FATAL_ERROR "This project is not supported on MacOS")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2 -s -DNDEBUG -flto")

add_executable(${PROJECT_NAME} main.c)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# cpack
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCHITECTURE})  
set(CPACK_PACKAGE_CONTACT "eldarielmario@gmail.com")

include(CPack)
