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
CMAKE_SOURCE_DIR = /Users/sean/vs_workspace/google_test/googletest/googletest/samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sean/vs_workspace/google_test/googletest/googletest/samples/build

# Include any dependencies generated for this target.
include CMakeFiles/MyTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyTest.dir/flags.make

CMakeFiles/MyTest.dir/sample1.cc.o: CMakeFiles/MyTest.dir/flags.make
CMakeFiles/MyTest.dir/sample1.cc.o: /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1.cc
CMakeFiles/MyTest.dir/sample1.cc.o: CMakeFiles/MyTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sean/vs_workspace/google_test/googletest/googletest/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyTest.dir/sample1.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTest.dir/sample1.cc.o -MF CMakeFiles/MyTest.dir/sample1.cc.o.d -o CMakeFiles/MyTest.dir/sample1.cc.o -c /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1.cc

CMakeFiles/MyTest.dir/sample1.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTest.dir/sample1.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1.cc > CMakeFiles/MyTest.dir/sample1.cc.i

CMakeFiles/MyTest.dir/sample1.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTest.dir/sample1.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1.cc -o CMakeFiles/MyTest.dir/sample1.cc.s

CMakeFiles/MyTest.dir/sample1_unittest.cc.o: CMakeFiles/MyTest.dir/flags.make
CMakeFiles/MyTest.dir/sample1_unittest.cc.o: /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1_unittest.cc
CMakeFiles/MyTest.dir/sample1_unittest.cc.o: CMakeFiles/MyTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sean/vs_workspace/google_test/googletest/googletest/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyTest.dir/sample1_unittest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTest.dir/sample1_unittest.cc.o -MF CMakeFiles/MyTest.dir/sample1_unittest.cc.o.d -o CMakeFiles/MyTest.dir/sample1_unittest.cc.o -c /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1_unittest.cc

CMakeFiles/MyTest.dir/sample1_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTest.dir/sample1_unittest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1_unittest.cc > CMakeFiles/MyTest.dir/sample1_unittest.cc.i

CMakeFiles/MyTest.dir/sample1_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTest.dir/sample1_unittest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sean/vs_workspace/google_test/googletest/googletest/samples/sample1_unittest.cc -o CMakeFiles/MyTest.dir/sample1_unittest.cc.s

# Object files for target MyTest
MyTest_OBJECTS = \
"CMakeFiles/MyTest.dir/sample1.cc.o" \
"CMakeFiles/MyTest.dir/sample1_unittest.cc.o"

# External object files for target MyTest
MyTest_EXTERNAL_OBJECTS =

MyTest: CMakeFiles/MyTest.dir/sample1.cc.o
MyTest: CMakeFiles/MyTest.dir/sample1_unittest.cc.o
MyTest: CMakeFiles/MyTest.dir/build.make
MyTest: /usr/local/lib/libgtest.a
MyTest: /usr/local/lib/libgtest_main.a
MyTest: CMakeFiles/MyTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sean/vs_workspace/google_test/googletest/googletest/samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable MyTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyTest.dir/build: MyTest
.PHONY : CMakeFiles/MyTest.dir/build

CMakeFiles/MyTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyTest.dir/clean

CMakeFiles/MyTest.dir/depend:
	cd /Users/sean/vs_workspace/google_test/googletest/googletest/samples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sean/vs_workspace/google_test/googletest/googletest/samples /Users/sean/vs_workspace/google_test/googletest/googletest/samples /Users/sean/vs_workspace/google_test/googletest/googletest/samples/build /Users/sean/vs_workspace/google_test/googletest/googletest/samples/build /Users/sean/vs_workspace/google_test/googletest/googletest/samples/build/CMakeFiles/MyTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyTest.dir/depend

