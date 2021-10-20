cmake_minimum_required(VERSION 3.5)
set(APPNAME "CppRestSdk_Demo")

project(${APPNAME}  LANGUAGES CXX)

# Threads
find_package(Threads REQUIRED)
include_directories(${Threads_INCLUDE_DIRS})
link_directories(${Threads_LIBRARY_DIRS})

#Cpp rest sdk
#https://github.com/microsoft/cpprestsdk
find_package(cpprestsdk REQUIRED)

set (SOURCES
    src/main.cpp
    src/cpprest/handler.cpp
    src/Student.cpp
    src/FakeDb.cpp
)

set(HEADERS
    src/stdafx.h
    src/cpprest/handler.h
    src/Student.hpp
    src/FakeDb.hpp
)


add_executable(${APPNAME} ${HEADERS} ${SOURCES} )
#target_link_libraries(${APPNAME} PRIVATE Threads::Threads -lcrypto cpprest  ${cpprestsdk_LIBRARIES}  ${GTest_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(${APPNAME} PRIVATE Threads::Threads -lcrypto cpprest  ${cpprestsdk_LIBRARIES})


#add_subdirectory(test)
