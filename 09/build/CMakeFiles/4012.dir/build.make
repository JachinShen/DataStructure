# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/jachinshen/Projects/Cpp/DataStructure/09

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jachinshen/Projects/Cpp/DataStructure/09/build

# Include any dependencies generated for this target.
include CMakeFiles/4012.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/4012.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4012.dir/flags.make

CMakeFiles/4012.dir/src/4012.cpp.o: CMakeFiles/4012.dir/flags.make
CMakeFiles/4012.dir/src/4012.cpp.o: ../src/4012.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jachinshen/Projects/Cpp/DataStructure/09/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4012.dir/src/4012.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/4012.dir/src/4012.cpp.o -c /home/jachinshen/Projects/Cpp/DataStructure/09/src/4012.cpp

CMakeFiles/4012.dir/src/4012.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4012.dir/src/4012.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jachinshen/Projects/Cpp/DataStructure/09/src/4012.cpp > CMakeFiles/4012.dir/src/4012.cpp.i

CMakeFiles/4012.dir/src/4012.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4012.dir/src/4012.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jachinshen/Projects/Cpp/DataStructure/09/src/4012.cpp -o CMakeFiles/4012.dir/src/4012.cpp.s

CMakeFiles/4012.dir/src/4012.cpp.o.requires:

.PHONY : CMakeFiles/4012.dir/src/4012.cpp.o.requires

CMakeFiles/4012.dir/src/4012.cpp.o.provides: CMakeFiles/4012.dir/src/4012.cpp.o.requires
	$(MAKE) -f CMakeFiles/4012.dir/build.make CMakeFiles/4012.dir/src/4012.cpp.o.provides.build
.PHONY : CMakeFiles/4012.dir/src/4012.cpp.o.provides

CMakeFiles/4012.dir/src/4012.cpp.o.provides.build: CMakeFiles/4012.dir/src/4012.cpp.o


# Object files for target 4012
4012_OBJECTS = \
"CMakeFiles/4012.dir/src/4012.cpp.o"

# External object files for target 4012
4012_EXTERNAL_OBJECTS =

4012: CMakeFiles/4012.dir/src/4012.cpp.o
4012: CMakeFiles/4012.dir/build.make
4012: CMakeFiles/4012.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jachinshen/Projects/Cpp/DataStructure/09/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 4012"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/4012.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4012.dir/build: 4012

.PHONY : CMakeFiles/4012.dir/build

CMakeFiles/4012.dir/requires: CMakeFiles/4012.dir/src/4012.cpp.o.requires

.PHONY : CMakeFiles/4012.dir/requires

CMakeFiles/4012.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/4012.dir/cmake_clean.cmake
.PHONY : CMakeFiles/4012.dir/clean

CMakeFiles/4012.dir/depend:
	cd /home/jachinshen/Projects/Cpp/DataStructure/09/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jachinshen/Projects/Cpp/DataStructure/09 /home/jachinshen/Projects/Cpp/DataStructure/09 /home/jachinshen/Projects/Cpp/DataStructure/09/build /home/jachinshen/Projects/Cpp/DataStructure/09/build /home/jachinshen/Projects/Cpp/DataStructure/09/build/CMakeFiles/4012.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/4012.dir/depend

