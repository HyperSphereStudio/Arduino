# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/JohnB/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/JohnB/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Arduino.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Arduino.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Arduino.dir/flags.make

CMakeFiles/Arduino.dir/Cirk1A.cpp.o: CMakeFiles/Arduino.dir/flags.make
CMakeFiles/Arduino.dir/Cirk1A.cpp.o: ../Cirk1A.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Arduino.dir/Cirk1A.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Arduino.dir/Cirk1A.cpp.o -c /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/Cirk1A.cpp

CMakeFiles/Arduino.dir/Cirk1A.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Arduino.dir/Cirk1A.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/Cirk1A.cpp > CMakeFiles/Arduino.dir/Cirk1A.cpp.i

CMakeFiles/Arduino.dir/Cirk1A.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Arduino.dir/Cirk1A.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/Cirk1A.cpp -o CMakeFiles/Arduino.dir/Cirk1A.cpp.s

# Object files for target Arduino
Arduino_OBJECTS = \
"CMakeFiles/Arduino.dir/Cirk1A.cpp.o"

# External object files for target Arduino
Arduino_EXTERNAL_OBJECTS =

Arduino.exe: CMakeFiles/Arduino.dir/Cirk1A.cpp.o
Arduino.exe: CMakeFiles/Arduino.dir/build.make
Arduino.exe: CMakeFiles/Arduino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Arduino.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Arduino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Arduino.dir/build: Arduino.exe

.PHONY : CMakeFiles/Arduino.dir/build

CMakeFiles/Arduino.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Arduino.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Arduino.dir/clean

CMakeFiles/Arduino.dir/depend:
	cd /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug /cygdrive/c/Users/JohnB/Documents/Arduino/MyLibs/Cirk1A/cmake-build-debug/CMakeFiles/Arduino.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Arduino.dir/depend

