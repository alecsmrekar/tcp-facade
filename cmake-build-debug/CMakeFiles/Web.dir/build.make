# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/145/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/145/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alec/CLionProjects/Web

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alec/CLionProjects/Web/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Web.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Web.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Web.dir/flags.make

CMakeFiles/Web.dir/main.c.o: CMakeFiles/Web.dir/flags.make
CMakeFiles/Web.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alec/CLionProjects/Web/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Web.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Web.dir/main.c.o   -c /home/alec/CLionProjects/Web/main.c

CMakeFiles/Web.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Web.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alec/CLionProjects/Web/main.c > CMakeFiles/Web.dir/main.c.i

CMakeFiles/Web.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Web.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alec/CLionProjects/Web/main.c -o CMakeFiles/Web.dir/main.c.s

# Object files for target Web
Web_OBJECTS = \
"CMakeFiles/Web.dir/main.c.o"

# External object files for target Web
Web_EXTERNAL_OBJECTS =

Web: CMakeFiles/Web.dir/main.c.o
Web: CMakeFiles/Web.dir/build.make
Web: CMakeFiles/Web.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alec/CLionProjects/Web/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Web"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Web.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Web.dir/build: Web

.PHONY : CMakeFiles/Web.dir/build

CMakeFiles/Web.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Web.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Web.dir/clean

CMakeFiles/Web.dir/depend:
	cd /home/alec/CLionProjects/Web/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alec/CLionProjects/Web /home/alec/CLionProjects/Web /home/alec/CLionProjects/Web/cmake-build-debug /home/alec/CLionProjects/Web/cmake-build-debug /home/alec/CLionProjects/Web/cmake-build-debug/CMakeFiles/Web.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Web.dir/depend

