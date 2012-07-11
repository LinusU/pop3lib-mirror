cmake_minimum_required(VERSION 2.6)
project(poplib)

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