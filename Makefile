# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake 2.8\bin\cmake.exe" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "C:\Program Files\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\daroo\workspace\poplib@poplib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\daroo\workspace\poplib@poplib

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake 2.8\bin\cmake-gui.exe" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake 2.8\bin\cmake.exe" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\daroo\workspace\poplib@poplib\CMakeFiles C:\Users\daroo\workspace\poplib@poplib\CMakeFiles\progress.marks
	$(MAKE) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\daroo\workspace\poplib@poplib\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named poplib

# Build rule for target.
poplib: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 poplib
.PHONY : poplib

# fast build rule for target.
poplib/fast:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/build
.PHONY : poplib/fast

#=============================================================================
# Target rules for targets named datTest

# Build rule for target.
datTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 datTest
.PHONY : datTest

# fast build rule for target.
datTest/fast:
	$(MAKE) -f tests\CMakeFiles\datTest.dir\build.make tests/CMakeFiles/datTest.dir/build
.PHONY : datTest/fast

#=============================================================================
# Target rules for targets named hdrTest

# Build rule for target.
hdrTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 hdrTest
.PHONY : hdrTest

# fast build rule for target.
hdrTest/fast:
	$(MAKE) -f tests\CMakeFiles\hdrTest.dir\build.make tests/CMakeFiles/hdrTest.dir/build
.PHONY : hdrTest/fast

#=============================================================================
# Target rules for targets named mappackTest

# Build rule for target.
mappackTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 mappackTest
.PHONY : mappackTest

# fast build rule for target.
mappackTest/fast:
	$(MAKE) -f tests\CMakeFiles\mappackTest.dir\build.make tests/CMakeFiles/mappackTest.dir/build
.PHONY : mappackTest/fast

src/Ip.obj: src/Ip.cpp.obj
.PHONY : src/Ip.obj

# target to build an object file
src/Ip.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Ip.cpp.obj
.PHONY : src/Ip.cpp.obj

src/Ip.i: src/Ip.cpp.i
.PHONY : src/Ip.i

# target to preprocess a source file
src/Ip.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Ip.cpp.i
.PHONY : src/Ip.cpp.i

src/Ip.s: src/Ip.cpp.s
.PHONY : src/Ip.s

# target to generate assembly for a file
src/Ip.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Ip.cpp.s
.PHONY : src/Ip.cpp.s

src/Map.obj: src/Map.cpp.obj
.PHONY : src/Map.obj

# target to build an object file
src/Map.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Map.cpp.obj
.PHONY : src/Map.cpp.obj

src/Map.i: src/Map.cpp.i
.PHONY : src/Map.i

# target to preprocess a source file
src/Map.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Map.cpp.i
.PHONY : src/Map.cpp.i

src/Map.s: src/Map.cpp.s
.PHONY : src/Map.s

# target to generate assembly for a file
src/Map.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Map.cpp.s
.PHONY : src/Map.cpp.s

src/MapDat.obj: src/MapDat.cpp.obj
.PHONY : src/MapDat.obj

# target to build an object file
src/MapDat.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapDat.cpp.obj
.PHONY : src/MapDat.cpp.obj

src/MapDat.i: src/MapDat.cpp.i
.PHONY : src/MapDat.i

# target to preprocess a source file
src/MapDat.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapDat.cpp.i
.PHONY : src/MapDat.cpp.i

src/MapDat.s: src/MapDat.cpp.s
.PHONY : src/MapDat.s

# target to generate assembly for a file
src/MapDat.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapDat.cpp.s
.PHONY : src/MapDat.cpp.s

src/MapHeader.obj: src/MapHeader.cpp.obj
.PHONY : src/MapHeader.obj

# target to build an object file
src/MapHeader.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapHeader.cpp.obj
.PHONY : src/MapHeader.cpp.obj

src/MapHeader.i: src/MapHeader.cpp.i
.PHONY : src/MapHeader.i

# target to preprocess a source file
src/MapHeader.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapHeader.cpp.i
.PHONY : src/MapHeader.cpp.i

src/MapHeader.s: src/MapHeader.cpp.s
.PHONY : src/MapHeader.s

# target to generate assembly for a file
src/MapHeader.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapHeader.cpp.s
.PHONY : src/MapHeader.cpp.s

src/MapLand.obj: src/MapLand.cpp.obj
.PHONY : src/MapLand.obj

# target to build an object file
src/MapLand.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapLand.cpp.obj
.PHONY : src/MapLand.cpp.obj

src/MapLand.i: src/MapLand.cpp.i
.PHONY : src/MapLand.i

# target to preprocess a source file
src/MapLand.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapLand.cpp.i
.PHONY : src/MapLand.cpp.i

src/MapLand.s: src/MapLand.cpp.s
.PHONY : src/MapLand.s

# target to generate assembly for a file
src/MapLand.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapLand.cpp.s
.PHONY : src/MapLand.cpp.s

src/MapObjDiscovery.obj: src/MapObjDiscovery.cpp.obj
.PHONY : src/MapObjDiscovery.obj

# target to build an object file
src/MapObjDiscovery.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjDiscovery.cpp.obj
.PHONY : src/MapObjDiscovery.cpp.obj

src/MapObjDiscovery.i: src/MapObjDiscovery.cpp.i
.PHONY : src/MapObjDiscovery.i

# target to preprocess a source file
src/MapObjDiscovery.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjDiscovery.cpp.i
.PHONY : src/MapObjDiscovery.cpp.i

src/MapObjDiscovery.s: src/MapObjDiscovery.cpp.s
.PHONY : src/MapObjDiscovery.s

# target to generate assembly for a file
src/MapObjDiscovery.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjDiscovery.cpp.s
.PHONY : src/MapObjDiscovery.cpp.s

src/MapObjTrigger.obj: src/MapObjTrigger.cpp.obj
.PHONY : src/MapObjTrigger.obj

# target to build an object file
src/MapObjTrigger.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjTrigger.cpp.obj
.PHONY : src/MapObjTrigger.cpp.obj

src/MapObjTrigger.i: src/MapObjTrigger.cpp.i
.PHONY : src/MapObjTrigger.i

# target to preprocess a source file
src/MapObjTrigger.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjTrigger.cpp.i
.PHONY : src/MapObjTrigger.cpp.i

src/MapObjTrigger.s: src/MapObjTrigger.cpp.s
.PHONY : src/MapObjTrigger.s

# target to generate assembly for a file
src/MapObjTrigger.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MapObjTrigger.cpp.s
.PHONY : src/MapObjTrigger.cpp.s

src/Mappack.obj: src/Mappack.cpp.obj
.PHONY : src/Mappack.obj

# target to build an object file
src/Mappack.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Mappack.cpp.obj
.PHONY : src/Mappack.cpp.obj

src/Mappack.i: src/Mappack.cpp.i
.PHONY : src/Mappack.i

# target to preprocess a source file
src/Mappack.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Mappack.cpp.i
.PHONY : src/Mappack.cpp.i

src/Mappack.s: src/Mappack.cpp.s
.PHONY : src/Mappack.s

# target to generate assembly for a file
src/Mappack.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/Mappack.cpp.s
.PHONY : src/Mappack.cpp.s

src/MappackMap.obj: src/MappackMap.cpp.obj
.PHONY : src/MappackMap.obj

# target to build an object file
src/MappackMap.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MappackMap.cpp.obj
.PHONY : src/MappackMap.cpp.obj

src/MappackMap.i: src/MappackMap.cpp.i
.PHONY : src/MappackMap.i

# target to preprocess a source file
src/MappackMap.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MappackMap.cpp.i
.PHONY : src/MappackMap.cpp.i

src/MappackMap.s: src/MappackMap.cpp.s
.PHONY : src/MappackMap.s

# target to generate assembly for a file
src/MappackMap.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/MappackMap.cpp.s
.PHONY : src/MappackMap.cpp.s

src/PopGame.obj: src/PopGame.cpp.obj
.PHONY : src/PopGame.obj

# target to build an object file
src/PopGame.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/PopGame.cpp.obj
.PHONY : src/PopGame.cpp.obj

src/PopGame.i: src/PopGame.cpp.i
.PHONY : src/PopGame.i

# target to preprocess a source file
src/PopGame.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/PopGame.cpp.i
.PHONY : src/PopGame.cpp.i

src/PopGame.s: src/PopGame.cpp.s
.PHONY : src/PopGame.s

# target to generate assembly for a file
src/PopGame.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/PopGame.cpp.s
.PHONY : src/PopGame.cpp.s

src/StrUtil.obj: src/StrUtil.cpp.obj
.PHONY : src/StrUtil.obj

# target to build an object file
src/StrUtil.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/StrUtil.cpp.obj
.PHONY : src/StrUtil.cpp.obj

src/StrUtil.i: src/StrUtil.cpp.i
.PHONY : src/StrUtil.i

# target to preprocess a source file
src/StrUtil.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/StrUtil.cpp.i
.PHONY : src/StrUtil.cpp.i

src/StrUtil.s: src/StrUtil.cpp.s
.PHONY : src/StrUtil.s

# target to generate assembly for a file
src/StrUtil.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/StrUtil.cpp.s
.PHONY : src/StrUtil.cpp.s

src/String16.obj: src/String16.cpp.obj
.PHONY : src/String16.obj

# target to build an object file
src/String16.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/String16.cpp.obj
.PHONY : src/String16.cpp.obj

src/String16.i: src/String16.cpp.i
.PHONY : src/String16.i

# target to preprocess a source file
src/String16.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/String16.cpp.i
.PHONY : src/String16.cpp.i

src/String16.s: src/String16.cpp.s
.PHONY : src/String16.s

# target to generate assembly for a file
src/String16.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/String16.cpp.s
.PHONY : src/String16.cpp.s

src/UTFConversion.obj: src/UTFConversion.cpp.obj
.PHONY : src/UTFConversion.obj

# target to build an object file
src/UTFConversion.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/UTFConversion.cpp.obj
.PHONY : src/UTFConversion.cpp.obj

src/UTFConversion.i: src/UTFConversion.cpp.i
.PHONY : src/UTFConversion.i

# target to preprocess a source file
src/UTFConversion.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/UTFConversion.cpp.i
.PHONY : src/UTFConversion.cpp.i

src/UTFConversion.s: src/UTFConversion.cpp.s
.PHONY : src/UTFConversion.s

# target to generate assembly for a file
src/UTFConversion.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/UTFConversion.cpp.s
.PHONY : src/UTFConversion.cpp.s

src/systemUtils/Dir.obj: src/systemUtils/Dir.cpp.obj
.PHONY : src/systemUtils/Dir.obj

# target to build an object file
src/systemUtils/Dir.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/Dir.cpp.obj
.PHONY : src/systemUtils/Dir.cpp.obj

src/systemUtils/Dir.i: src/systemUtils/Dir.cpp.i
.PHONY : src/systemUtils/Dir.i

# target to preprocess a source file
src/systemUtils/Dir.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/Dir.cpp.i
.PHONY : src/systemUtils/Dir.cpp.i

src/systemUtils/Dir.s: src/systemUtils/Dir.cpp.s
.PHONY : src/systemUtils/Dir.s

# target to generate assembly for a file
src/systemUtils/Dir.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/Dir.cpp.s
.PHONY : src/systemUtils/Dir.cpp.s

src/systemUtils/File.obj: src/systemUtils/File.cpp.obj
.PHONY : src/systemUtils/File.obj

# target to build an object file
src/systemUtils/File.cpp.obj:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/File.cpp.obj
.PHONY : src/systemUtils/File.cpp.obj

src/systemUtils/File.i: src/systemUtils/File.cpp.i
.PHONY : src/systemUtils/File.i

# target to preprocess a source file
src/systemUtils/File.cpp.i:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/File.cpp.i
.PHONY : src/systemUtils/File.cpp.i

src/systemUtils/File.s: src/systemUtils/File.cpp.s
.PHONY : src/systemUtils/File.s

# target to generate assembly for a file
src/systemUtils/File.cpp.s:
	$(MAKE) -f CMakeFiles\poplib.dir\build.make CMakeFiles/poplib.dir/src/systemUtils/File.cpp.s
.PHONY : src/systemUtils/File.cpp.s

# Help Target
help:
	@$(CMAKE_COMMAND) -E echo "The following are some of the valid targets for this Makefile:"
	@$(CMAKE_COMMAND) -E echo "... all (the default if no target is provided)"
	@$(CMAKE_COMMAND) -E echo "... clean"
	@$(CMAKE_COMMAND) -E echo "... depend"
	@$(CMAKE_COMMAND) -E echo "... edit_cache"
	@$(CMAKE_COMMAND) -E echo "... poplib"
	@$(CMAKE_COMMAND) -E echo "... rebuild_cache"
	@$(CMAKE_COMMAND) -E echo "... datTest"
	@$(CMAKE_COMMAND) -E echo "... hdrTest"
	@$(CMAKE_COMMAND) -E echo "... mappackTest"
	@$(CMAKE_COMMAND) -E echo "... src/Ip.obj"
	@$(CMAKE_COMMAND) -E echo "... src/Ip.i"
	@$(CMAKE_COMMAND) -E echo "... src/Ip.s"
	@$(CMAKE_COMMAND) -E echo "... src/Map.obj"
	@$(CMAKE_COMMAND) -E echo "... src/Map.i"
	@$(CMAKE_COMMAND) -E echo "... src/Map.s"
	@$(CMAKE_COMMAND) -E echo "... src/MapDat.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MapDat.i"
	@$(CMAKE_COMMAND) -E echo "... src/MapDat.s"
	@$(CMAKE_COMMAND) -E echo "... src/MapHeader.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MapHeader.i"
	@$(CMAKE_COMMAND) -E echo "... src/MapHeader.s"
	@$(CMAKE_COMMAND) -E echo "... src/MapLand.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MapLand.i"
	@$(CMAKE_COMMAND) -E echo "... src/MapLand.s"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjDiscovery.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjDiscovery.i"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjDiscovery.s"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjTrigger.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjTrigger.i"
	@$(CMAKE_COMMAND) -E echo "... src/MapObjTrigger.s"
	@$(CMAKE_COMMAND) -E echo "... src/Mappack.obj"
	@$(CMAKE_COMMAND) -E echo "... src/Mappack.i"
	@$(CMAKE_COMMAND) -E echo "... src/Mappack.s"
	@$(CMAKE_COMMAND) -E echo "... src/MappackMap.obj"
	@$(CMAKE_COMMAND) -E echo "... src/MappackMap.i"
	@$(CMAKE_COMMAND) -E echo "... src/MappackMap.s"
	@$(CMAKE_COMMAND) -E echo "... src/PopGame.obj"
	@$(CMAKE_COMMAND) -E echo "... src/PopGame.i"
	@$(CMAKE_COMMAND) -E echo "... src/PopGame.s"
	@$(CMAKE_COMMAND) -E echo "... src/StrUtil.obj"
	@$(CMAKE_COMMAND) -E echo "... src/StrUtil.i"
	@$(CMAKE_COMMAND) -E echo "... src/StrUtil.s"
	@$(CMAKE_COMMAND) -E echo "... src/String16.obj"
	@$(CMAKE_COMMAND) -E echo "... src/String16.i"
	@$(CMAKE_COMMAND) -E echo "... src/String16.s"
	@$(CMAKE_COMMAND) -E echo "... src/UTFConversion.obj"
	@$(CMAKE_COMMAND) -E echo "... src/UTFConversion.i"
	@$(CMAKE_COMMAND) -E echo "... src/UTFConversion.s"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/Dir.obj"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/Dir.i"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/Dir.s"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/File.obj"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/File.i"
	@$(CMAKE_COMMAND) -E echo "... src/systemUtils/File.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

