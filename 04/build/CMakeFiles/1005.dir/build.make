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
CMAKE_SOURCE_DIR = /home/jachinshen/Projects/Cpp/DataStructure/04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jachinshen/Projects/Cpp/DataStructure/04/build

# Include any dependencies generated for this target.
include CMakeFiles/1005.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1005.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1005.dir/flags.make

CMakeFiles/1005.dir/src/1005.cpp.o: CMakeFiles/1005.dir/flags.make
CMakeFiles/1005.dir/src/1005.cpp.o: ../src/1005.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jachinshen/Projects/Cpp/DataStructure/04/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1005.dir/src/1005.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1005.dir/src/1005.cpp.o -c /home/jachinshen/Projects/Cpp/DataStructure/04/src/1005.cpp

CMakeFiles/1005.dir/src/1005.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1005.dir/src/1005.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jachinshen/Projects/Cpp/DataStructure/04/src/1005.cpp > CMakeFiles/1005.dir/src/1005.cpp.i

CMakeFiles/1005.dir/src/1005.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1005.dir/src/1005.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jachinshen/Projects/Cpp/DataStructure/04/src/1005.cpp -o CMakeFiles/1005.dir/src/1005.cpp.s

CMakeFiles/1005.dir/src/1005.cpp.o.requires:

.PHONY : CMakeFiles/1005.dir/src/1005.cpp.o.requires

CMakeFiles/1005.dir/src/1005.cpp.o.provides: CMakeFiles/1005.dir/src/1005.cpp.o.requires
	$(MAKE) -f CMakeFiles/1005.dir/build.make CMakeFiles/1005.dir/src/1005.cpp.o.provides.build
.PHONY : CMakeFiles/1005.dir/src/1005.cpp.o.provides

CMakeFiles/1005.dir/src/1005.cpp.o.provides.build: CMakeFiles/1005.dir/src/1005.cpp.o


# Object files for target 1005
1005_OBJECTS = \
"CMakeFiles/1005.dir/src/1005.cpp.o"

# External object files for target 1005
1005_EXTERNAL_OBJECTS =

1005: CMakeFiles/1005.dir/src/1005.cpp.o
1005: CMakeFiles/1005.dir/build.make
1005: CMakeFiles/1005.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jachinshen/Projects/Cpp/DataStructure/04/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1005"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1005.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1005.dir/build: 1005

.PHONY : CMakeFiles/1005.dir/build

CMakeFiles/1005.dir/requires: CMakeFiles/1005.dir/src/1005.cpp.o.requires

.PHONY : CMakeFiles/1005.dir/requires

CMakeFiles/1005.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1005.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1005.dir/clean

CMakeFiles/1005.dir/depend:
	cd /home/jachinshen/Projects/Cpp/DataStructure/04/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jachinshen/Projects/Cpp/DataStructure/04 /home/jachinshen/Projects/Cpp/DataStructure/04 /home/jachinshen/Projects/Cpp/DataStructure/04/build /home/jachinshen/Projects/Cpp/DataStructure/04/build /home/jachinshen/Projects/Cpp/DataStructure/04/build/CMakeFiles/1005.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1005.dir/depend

