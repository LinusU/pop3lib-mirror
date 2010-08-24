cmake_minimum_required(VERSION 2.6)
project(tests)

set(datTest_SRCS
	datTest.cpp)

add_executable(datTest ${datTest_SRCS})
target_link_libraries(datTest poplib)


set(hdrTest_SRCS
	hdrTest.cpp)

add_executable(hdrTest ${hdrTest_SRCS})
target_link_libraries(hdrTest poplib)

set(mappackTest_SRCS
	mappackTest.cpp)

add_executable(mappackTest ${mappackTest_SRCS})
target_link_libraries(mappackTest poplib)

set(objetcsTest_SRCS
	objectsTest.cpp)

add_executable(objectsTest ${objetcsTest_SRCS})
target_link_libraries(objectsTest poplib)