# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/asica/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/asica/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/asica/repo/studia/porr/tsp/brute-force

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/asica/repo/studia/porr/tsp/brute-force

# Include any dependencies generated for this target.
include CMakeFiles/salesman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/salesman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/salesman.dir/flags.make

CMakeFiles/salesman.dir/main.cpp.o: CMakeFiles/salesman.dir/flags.make
CMakeFiles/salesman.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/asica/repo/studia/porr/tsp/brute-force/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/salesman.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/salesman.dir/main.cpp.o -c /home/asica/repo/studia/porr/tsp/brute-force/main.cpp

CMakeFiles/salesman.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/salesman.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asica/repo/studia/porr/tsp/brute-force/main.cpp > CMakeFiles/salesman.dir/main.cpp.i

CMakeFiles/salesman.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/salesman.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asica/repo/studia/porr/tsp/brute-force/main.cpp -o CMakeFiles/salesman.dir/main.cpp.s

CMakeFiles/salesman.dir/graph.cpp.o: CMakeFiles/salesman.dir/flags.make
CMakeFiles/salesman.dir/graph.cpp.o: graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/asica/repo/studia/porr/tsp/brute-force/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/salesman.dir/graph.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/salesman.dir/graph.cpp.o -c /home/asica/repo/studia/porr/tsp/brute-force/graph.cpp

CMakeFiles/salesman.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/salesman.dir/graph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asica/repo/studia/porr/tsp/brute-force/graph.cpp > CMakeFiles/salesman.dir/graph.cpp.i

CMakeFiles/salesman.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/salesman.dir/graph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asica/repo/studia/porr/tsp/brute-force/graph.cpp -o CMakeFiles/salesman.dir/graph.cpp.s

# Object files for target salesman
salesman_OBJECTS = \
"CMakeFiles/salesman.dir/main.cpp.o" \
"CMakeFiles/salesman.dir/graph.cpp.o"

# External object files for target salesman
salesman_EXTERNAL_OBJECTS =

salesman: CMakeFiles/salesman.dir/main.cpp.o
salesman: CMakeFiles/salesman.dir/graph.cpp.o
salesman: CMakeFiles/salesman.dir/build.make
salesman: CMakeFiles/salesman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/asica/repo/studia/porr/tsp/brute-force/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable salesman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/salesman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/salesman.dir/build: salesman

.PHONY : CMakeFiles/salesman.dir/build

CMakeFiles/salesman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/salesman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/salesman.dir/clean

CMakeFiles/salesman.dir/depend:
	cd /home/asica/repo/studia/porr/tsp/brute-force && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/asica/repo/studia/porr/tsp/brute-force /home/asica/repo/studia/porr/tsp/brute-force /home/asica/repo/studia/porr/tsp/brute-force /home/asica/repo/studia/porr/tsp/brute-force /home/asica/repo/studia/porr/tsp/brute-force/CMakeFiles/salesman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/salesman.dir/depend
