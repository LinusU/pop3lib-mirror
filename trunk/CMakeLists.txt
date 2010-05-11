cmake_minimum_required(VERSION 2.6)
project(poplib)

include_directories(${CMAKE_HOME_DIRECTORY}/include)
include_directories(${CMAKE_HOME_DIRECTORY}/include/dmkp)

set(poplib_SRCS
	src/StrUtil.cpp
	src/MapDat.cpp
	src/MapHeader.cpp
	src/Map.cpp
	src/MapObjDiscovery.cpp
	src/MapObjTrigger.cpp
	src/MapLand.cpp
	src/Ip.cpp
	src/PopGame.cpp
	src/MappackMap.cpp
	src/MappackMap.cpp

	src/dmkp/cString.cpp
	src/dmkp/cStringArray.cpp
	src/dmkp/cStringBuilder.cpp
	src/dmkp/Colour.cpp
	src/dmkp/RAW.cpp
	src/dmkp/File.cpp
	src/dmkp/FileInfo.cpp
	src/dmkp/FileReader.cpp
	src/dmkp/FileWriter.cpp
	src/dmkp/cWavFile.cpp
	src/dmkp/popData.cpp
	src/dmkp/memory.cpp
	src/dmkp/messageBox.cpp
	src/dmkp/PopSound.cpp
	src/dmkp/cPopSoundManager.cpp
	src/dmkp/PopObject.cpp
	src/dmkp/cPopMemory.cpp
	src/dmkp/cMapManager.cpp)

add_library(poplib STATIC ${poplib_SRCS})

add_subdirectory(tests)