cmake_minimum_required(VERSION 3.5)
set(APPNAME "04_cppRestSdkInDocker")

project(${APPNAME} LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

# Threads
find_package(Threads REQUIRED)
include_directories(${Threads_INCLUDE_DIRS})
link_directories(${Threads_LIBRARY_DIRS})

# GTest
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})
link_directories(${GTest_LIBRARY_DIRS})


#sudo apt-get install cmake libgtest-dev
#cd /usr/src/gtest
#sudo cmake CMakeLists.txt
#sudo make
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
#sudo cp *.a /usr/lib


# Boost
find_package(Boost COMPONENTS system python filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Cpp rest sdk
#https://github.com/microsoft/cpprestsdk
find_package(cpprestsdk REQUIRED)

set (SOURCES
    main.cpp
    cpprest/handler.cpp
    FakeDb.cpp
)

set(HEADERS
    stdafx.h
    cpprest/handler.h
    FakeDb.hpp
)


add_executable(${APPNAME} ${HEADERS} ${SOURCES} )
target_link_libraries(${APPNAME} PRIVATE Threads::Threads -lcrypto cpprest  ${cpprestsdk_LIBRARIES}  ${GTest_LIBRARIES} ${Boost_LIBRARIES})


#add_subdirectory(test)
