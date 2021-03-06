# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nick/LoraDataHandleByC/loraserverByc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nick/LoraDataHandleByC/loraserverByc

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nick/LoraDataHandleByC/loraserverByc/CMakeFiles /home/nick/LoraDataHandleByC/loraserverByc/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nick/LoraDataHandleByC/loraserverByc/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named LoraHandlByC

# Build rule for target.
LoraHandlByC: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 LoraHandlByC
.PHONY : LoraHandlByC

# fast build rule for target.
LoraHandlByC/fast:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/build
.PHONY : LoraHandlByC/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/main.cpp.s
.PHONY : main.cpp.s

src/dbHandle.o: src/dbHandle.cpp.o

.PHONY : src/dbHandle.o

# target to build an object file
src/dbHandle.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/dbHandle.cpp.o
.PHONY : src/dbHandle.cpp.o

src/dbHandle.i: src/dbHandle.cpp.i

.PHONY : src/dbHandle.i

# target to preprocess a source file
src/dbHandle.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/dbHandle.cpp.i
.PHONY : src/dbHandle.cpp.i

src/dbHandle.s: src/dbHandle.cpp.s

.PHONY : src/dbHandle.s

# target to generate assembly for a file
src/dbHandle.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/dbHandle.cpp.s
.PHONY : src/dbHandle.cpp.s

src/initValue.o: src/initValue.cpp.o

.PHONY : src/initValue.o

# target to build an object file
src/initValue.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/initValue.cpp.o
.PHONY : src/initValue.cpp.o

src/initValue.i: src/initValue.cpp.i

.PHONY : src/initValue.i

# target to preprocess a source file
src/initValue.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/initValue.cpp.i
.PHONY : src/initValue.cpp.i

src/initValue.s: src/initValue.cpp.s

.PHONY : src/initValue.s

# target to generate assembly for a file
src/initValue.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/initValue.cpp.s
.PHONY : src/initValue.cpp.s

src/jsonHandle.o: src/jsonHandle.cpp.o

.PHONY : src/jsonHandle.o

# target to build an object file
src/jsonHandle.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/jsonHandle.cpp.o
.PHONY : src/jsonHandle.cpp.o

src/jsonHandle.i: src/jsonHandle.cpp.i

.PHONY : src/jsonHandle.i

# target to preprocess a source file
src/jsonHandle.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/jsonHandle.cpp.i
.PHONY : src/jsonHandle.cpp.i

src/jsonHandle.s: src/jsonHandle.cpp.s

.PHONY : src/jsonHandle.s

# target to generate assembly for a file
src/jsonHandle.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/jsonHandle.cpp.s
.PHONY : src/jsonHandle.cpp.s

src/mainprocess.o: src/mainprocess.cpp.o

.PHONY : src/mainprocess.o

# target to build an object file
src/mainprocess.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mainprocess.cpp.o
.PHONY : src/mainprocess.cpp.o

src/mainprocess.i: src/mainprocess.cpp.i

.PHONY : src/mainprocess.i

# target to preprocess a source file
src/mainprocess.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mainprocess.cpp.i
.PHONY : src/mainprocess.cpp.i

src/mainprocess.s: src/mainprocess.cpp.s

.PHONY : src/mainprocess.s

# target to generate assembly for a file
src/mainprocess.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mainprocess.cpp.s
.PHONY : src/mainprocess.cpp.s

src/mqttHandle.o: src/mqttHandle.cpp.o

.PHONY : src/mqttHandle.o

# target to build an object file
src/mqttHandle.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mqttHandle.cpp.o
.PHONY : src/mqttHandle.cpp.o

src/mqttHandle.i: src/mqttHandle.cpp.i

.PHONY : src/mqttHandle.i

# target to preprocess a source file
src/mqttHandle.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mqttHandle.cpp.i
.PHONY : src/mqttHandle.cpp.i

src/mqttHandle.s: src/mqttHandle.cpp.s

.PHONY : src/mqttHandle.s

# target to generate assembly for a file
src/mqttHandle.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/mqttHandle.cpp.s
.PHONY : src/mqttHandle.cpp.s

src/pqDbHandle.o: src/pqDbHandle.cpp.o

.PHONY : src/pqDbHandle.o

# target to build an object file
src/pqDbHandle.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/pqDbHandle.cpp.o
.PHONY : src/pqDbHandle.cpp.o

src/pqDbHandle.i: src/pqDbHandle.cpp.i

.PHONY : src/pqDbHandle.i

# target to preprocess a source file
src/pqDbHandle.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/pqDbHandle.cpp.i
.PHONY : src/pqDbHandle.cpp.i

src/pqDbHandle.s: src/pqDbHandle.cpp.s

.PHONY : src/pqDbHandle.s

# target to generate assembly for a file
src/pqDbHandle.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/pqDbHandle.cpp.s
.PHONY : src/pqDbHandle.cpp.s

src/transmit.o: src/transmit.cpp.o

.PHONY : src/transmit.o

# target to build an object file
src/transmit.cpp.o:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/transmit.cpp.o
.PHONY : src/transmit.cpp.o

src/transmit.i: src/transmit.cpp.i

.PHONY : src/transmit.i

# target to preprocess a source file
src/transmit.cpp.i:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/transmit.cpp.i
.PHONY : src/transmit.cpp.i

src/transmit.s: src/transmit.cpp.s

.PHONY : src/transmit.s

# target to generate assembly for a file
src/transmit.cpp.s:
	$(MAKE) -f CMakeFiles/LoraHandlByC.dir/build.make CMakeFiles/LoraHandlByC.dir/src/transmit.cpp.s
.PHONY : src/transmit.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... LoraHandlByC"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/dbHandle.o"
	@echo "... src/dbHandle.i"
	@echo "... src/dbHandle.s"
	@echo "... src/initValue.o"
	@echo "... src/initValue.i"
	@echo "... src/initValue.s"
	@echo "... src/jsonHandle.o"
	@echo "... src/jsonHandle.i"
	@echo "... src/jsonHandle.s"
	@echo "... src/mainprocess.o"
	@echo "... src/mainprocess.i"
	@echo "... src/mainprocess.s"
	@echo "... src/mqttHandle.o"
	@echo "... src/mqttHandle.i"
	@echo "... src/mqttHandle.s"
	@echo "... src/pqDbHandle.o"
	@echo "... src/pqDbHandle.i"
	@echo "... src/pqDbHandle.s"
	@echo "... src/transmit.o"
	@echo "... src/transmit.i"
	@echo "... src/transmit.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

