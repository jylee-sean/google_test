# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sean/vs_workspace/google_test/googletest/googlemock/sample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build

# Include any dependencies generated for this target.
include CMakeFiles/MyTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyTest.dir/flags.make

CMakeFiles/MyTest.dir/test.cc.o: CMakeFiles/MyTest.dir/flags.make
CMakeFiles/MyTest.dir/test.cc.o: /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/test.cc
CMakeFiles/MyTest.dir/test.cc.o: CMakeFiles/MyTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyTest.dir/test.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTest.dir/test.cc.o -MF CMakeFiles/MyTest.dir/test.cc.o.d -o CMakeFiles/MyTest.dir/test.cc.o -c /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/test.cc

CMakeFiles/MyTest.dir/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTest.dir/test.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/test.cc > CMakeFiles/MyTest.dir/test.cc.i

CMakeFiles/MyTest.dir/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTest.dir/test.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/test.cc -o CMakeFiles/MyTest.dir/test.cc.s

# Object files for target MyTest
MyTest_OBJECTS = \
"CMakeFiles/MyTest.dir/test.cc.o"

# External object files for target MyTest
MyTest_EXTERNAL_OBJECTS =

MyTest: CMakeFiles/MyTest.dir/test.cc.o
MyTest: CMakeFiles/MyTest.dir/build.make
MyTest: /usr/local/lib/libgtest.a
MyTest: /usr/local/lib/libgtest_main.a
MyTest: /usr/local/lib/libgmock.a
MyTest: /usr/local/lib/libgmock_main.a
MyTest: CMakeFiles/MyTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyTest.dir/build: MyTest
.PHONY : CMakeFiles/MyTest.dir/build

CMakeFiles/MyTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyTest.dir/clean

CMakeFiles/MyTest.dir/depend:
	cd /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sean/vs_workspace/google_test/googletest/googlemock/sample /Users/sean/vs_workspace/google_test/googletest/googlemock/sample /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build /Users/sean/vs_workspace/google_test/googletest/googlemock/sample/build/CMakeFiles/MyTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyTest.dir/depend

