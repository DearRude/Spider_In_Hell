# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/dearrude/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dearrude/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dearrude/CLionProjects/Spider-In-Hell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Spider_In_Hell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Spider_In_Hell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Spider_In_Hell.dir/flags.make

CMakeFiles/Spider_In_Hell.dir/main.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Spider_In_Hell.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/main.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/main.c

CMakeFiles/Spider_In_Hell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/main.c > CMakeFiles/Spider_In_Hell.dir/main.c.i

CMakeFiles/Spider_In_Hell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/main.c -o CMakeFiles/Spider_In_Hell.dir/main.c.s

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o: ../graphic/screens/screen_ending.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_ending.c

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_ending.c > CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.i

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_ending.c -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.s

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o: ../graphic/screens/screen_gameplay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_gameplay.c

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_gameplay.c > CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.i

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_gameplay.c -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.s

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o: ../graphic/screens/screen_logo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_logo.c

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_logo.c > CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.i

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_logo.c -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.s

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o: ../graphic/screens/screen_title.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_title.c

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_title.c > CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.i

CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/graphic/screens/screen_title.c -o CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.s

CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o: ../gameFlow.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/gameFlow.c

CMakeFiles/Spider_In_Hell.dir/gameFlow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/gameFlow.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/gameFlow.c > CMakeFiles/Spider_In_Hell.dir/gameFlow.c.i

CMakeFiles/Spider_In_Hell.dir/gameFlow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/gameFlow.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/gameFlow.c -o CMakeFiles/Spider_In_Hell.dir/gameFlow.c.s

CMakeFiles/Spider_In_Hell.dir/gravity.c.o: CMakeFiles/Spider_In_Hell.dir/flags.make
CMakeFiles/Spider_In_Hell.dir/gravity.c.o: ../gravity.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Spider_In_Hell.dir/gravity.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Spider_In_Hell.dir/gravity.c.o   -c /home/dearrude/CLionProjects/Spider-In-Hell/gravity.c

CMakeFiles/Spider_In_Hell.dir/gravity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Spider_In_Hell.dir/gravity.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dearrude/CLionProjects/Spider-In-Hell/gravity.c > CMakeFiles/Spider_In_Hell.dir/gravity.c.i

CMakeFiles/Spider_In_Hell.dir/gravity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Spider_In_Hell.dir/gravity.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dearrude/CLionProjects/Spider-In-Hell/gravity.c -o CMakeFiles/Spider_In_Hell.dir/gravity.c.s

# Object files for target Spider_In_Hell
Spider_In_Hell_OBJECTS = \
"CMakeFiles/Spider_In_Hell.dir/main.c.o" \
"CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o" \
"CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o" \
"CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o" \
"CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o" \
"CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o" \
"CMakeFiles/Spider_In_Hell.dir/gravity.c.o"

# External object files for target Spider_In_Hell
Spider_In_Hell_EXTERNAL_OBJECTS =

Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/main.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_ending.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_gameplay.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_logo.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/graphic/screens/screen_title.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/gameFlow.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/gravity.c.o
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/build.make
Spider_In_Hell: CMakeFiles/Spider_In_Hell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable Spider_In_Hell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Spider_In_Hell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Spider_In_Hell.dir/build: Spider_In_Hell

.PHONY : CMakeFiles/Spider_In_Hell.dir/build

CMakeFiles/Spider_In_Hell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Spider_In_Hell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Spider_In_Hell.dir/clean

CMakeFiles/Spider_In_Hell.dir/depend:
	cd /home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dearrude/CLionProjects/Spider-In-Hell /home/dearrude/CLionProjects/Spider-In-Hell /home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug /home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug /home/dearrude/CLionProjects/Spider-In-Hell/cmake-build-debug/CMakeFiles/Spider_In_Hell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Spider_In_Hell.dir/depend

