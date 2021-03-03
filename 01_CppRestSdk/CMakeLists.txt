cmake_minimum_required(VERSION 3.5)
set(APPNAME "dockerTesting")

project(${APPNAME}  LANGUAGES CXX)

# Threads
find_package(Threads REQUIRED)
include_directories(${Threads_INCLUDE_DIRS})
link_directories(${Threads_LIBRARY_DIRS})

# GTest
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})
link_directories(${GTest_LIBRARY_DIRS})

#CppRestSdk
find_package(cpprestsdk REQUIRED)
include_directories(${cpprestsdk_INCLUDE_DIRS})
link_directories(${cpprestsdk_LIBRARY_DIRS})

#casablanca install notes
#https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Linux
#https://github.com/microsoft/cpprestsdk/issues/1388


# Boost
find_package(Boost COMPONENTS system python filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set (SOURCES
    src/main.cpp
    src/cpprest/handler.cpp
)

set(HEADERS
    src/stdafx.h
    src/cpprest/handler.h
)


add_executable(${APPNAME} ${HEADERS} ${SOURCES} )
#target_link_libraries(${APPNAME}  PRIVATE cpprestsdk_openssl_internal INTERFACE OpenSSL::SSL)
target_link_libraries(${APPNAME}  PRIVATE -lcrypto cpprest  ${cpprestsdk_LIBRARIES} ${GTest_LIBRARIES} ${Boost_LIBRARIES})
