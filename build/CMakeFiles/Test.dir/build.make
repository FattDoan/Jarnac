# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fatt/ProgImperative/Projet-Jarnac

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fatt/ProgImperative/Projet-Jarnac/build

# Include any dependencies generated for this target.
include CMakeFiles/Test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test.dir/flags.make

CMakeFiles/Test.dir/tests/moteur-test.cpp.o: CMakeFiles/Test.dir/flags.make
CMakeFiles/Test.dir/tests/moteur-test.cpp.o: ../tests/moteur-test.cpp
CMakeFiles/Test.dir/tests/moteur-test.cpp.o: CMakeFiles/Test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fatt/ProgImperative/Projet-Jarnac/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test.dir/tests/moteur-test.cpp.o"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test.dir/tests/moteur-test.cpp.o -MF CMakeFiles/Test.dir/tests/moteur-test.cpp.o.d -o CMakeFiles/Test.dir/tests/moteur-test.cpp.o -c /home/fatt/ProgImperative/Projet-Jarnac/tests/moteur-test.cpp

CMakeFiles/Test.dir/tests/moteur-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test.dir/tests/moteur-test.cpp.i"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fatt/ProgImperative/Projet-Jarnac/tests/moteur-test.cpp > CMakeFiles/Test.dir/tests/moteur-test.cpp.i

CMakeFiles/Test.dir/tests/moteur-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test.dir/tests/moteur-test.cpp.s"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fatt/ProgImperative/Projet-Jarnac/tests/moteur-test.cpp -o CMakeFiles/Test.dir/tests/moteur-test.cpp.s

CMakeFiles/Test.dir/src/moteur.cpp.o: CMakeFiles/Test.dir/flags.make
CMakeFiles/Test.dir/src/moteur.cpp.o: ../src/moteur.cpp
CMakeFiles/Test.dir/src/moteur.cpp.o: CMakeFiles/Test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fatt/ProgImperative/Projet-Jarnac/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Test.dir/src/moteur.cpp.o"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test.dir/src/moteur.cpp.o -MF CMakeFiles/Test.dir/src/moteur.cpp.o.d -o CMakeFiles/Test.dir/src/moteur.cpp.o -c /home/fatt/ProgImperative/Projet-Jarnac/src/moteur.cpp

CMakeFiles/Test.dir/src/moteur.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test.dir/src/moteur.cpp.i"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fatt/ProgImperative/Projet-Jarnac/src/moteur.cpp > CMakeFiles/Test.dir/src/moteur.cpp.i

CMakeFiles/Test.dir/src/moteur.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test.dir/src/moteur.cpp.s"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fatt/ProgImperative/Projet-Jarnac/src/moteur.cpp -o CMakeFiles/Test.dir/src/moteur.cpp.s

CMakeFiles/Test.dir/src/gestionDict.cpp.o: CMakeFiles/Test.dir/flags.make
CMakeFiles/Test.dir/src/gestionDict.cpp.o: ../src/gestionDict.cpp
CMakeFiles/Test.dir/src/gestionDict.cpp.o: CMakeFiles/Test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fatt/ProgImperative/Projet-Jarnac/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Test.dir/src/gestionDict.cpp.o"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test.dir/src/gestionDict.cpp.o -MF CMakeFiles/Test.dir/src/gestionDict.cpp.o.d -o CMakeFiles/Test.dir/src/gestionDict.cpp.o -c /home/fatt/ProgImperative/Projet-Jarnac/src/gestionDict.cpp

CMakeFiles/Test.dir/src/gestionDict.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test.dir/src/gestionDict.cpp.i"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fatt/ProgImperative/Projet-Jarnac/src/gestionDict.cpp > CMakeFiles/Test.dir/src/gestionDict.cpp.i

CMakeFiles/Test.dir/src/gestionDict.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test.dir/src/gestionDict.cpp.s"
	/home/fatt/miniforge3/envs/info-111/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fatt/ProgImperative/Projet-Jarnac/src/gestionDict.cpp -o CMakeFiles/Test.dir/src/gestionDict.cpp.s

# Object files for target Test
Test_OBJECTS = \
"CMakeFiles/Test.dir/tests/moteur-test.cpp.o" \
"CMakeFiles/Test.dir/src/moteur.cpp.o" \
"CMakeFiles/Test.dir/src/gestionDict.cpp.o"

# External object files for target Test
Test_EXTERNAL_OBJECTS =

Test: CMakeFiles/Test.dir/tests/moteur-test.cpp.o
Test: CMakeFiles/Test.dir/src/moteur.cpp.o
Test: CMakeFiles/Test.dir/src/gestionDict.cpp.o
Test: CMakeFiles/Test.dir/build.make
Test: CMakeFiles/Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fatt/ProgImperative/Projet-Jarnac/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test.dir/build: Test
.PHONY : CMakeFiles/Test.dir/build

CMakeFiles/Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test.dir/clean

CMakeFiles/Test.dir/depend:
	cd /home/fatt/ProgImperative/Projet-Jarnac/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fatt/ProgImperative/Projet-Jarnac /home/fatt/ProgImperative/Projet-Jarnac /home/fatt/ProgImperative/Projet-Jarnac/build /home/fatt/ProgImperative/Projet-Jarnac/build /home/fatt/ProgImperative/Projet-Jarnac/build/CMakeFiles/Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test.dir/depend

