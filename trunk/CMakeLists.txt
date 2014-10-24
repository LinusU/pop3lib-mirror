cmake_minimum_required(VERSION 2.6)
project(poplib)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized")
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -Wempty-body -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized")
endif()

include_directories(include)

set(poplib_SRCS
        src/StrUtil.cpp
        src/UTFConversion.cpp
        src/String16.cpp
        src/MapObjGeneric.cpp
        src/MapDat.cpp
        src/MapHeader.cpp
        src/Map.cpp
        src/MapLand.cpp
        src/Ip.cpp
        src/PopGame.cpp
        src/MappackMap.cpp
        src/Mappack.cpp
        src/systemUtils/Dir.cpp
        src/systemUtils/File.cpp)

add_library(poplib STATIC ${poplib_SRCS})
