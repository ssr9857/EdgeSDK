# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/firefly/Documents/Seaway/SeawayEdgeSDK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/firefly/Documents/Seaway/SeawayEdgeSDK/build

# Include any dependencies generated for this target.
include CMakeFiles/edge_sdk.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/edge_sdk.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edge_sdk.dir/flags.make

CMakeFiles/edge_sdk.dir/src/base64.cpp.o: CMakeFiles/edge_sdk.dir/flags.make
CMakeFiles/edge_sdk.dir/src/base64.cpp.o: ../src/base64.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/edge_sdk.dir/src/base64.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edge_sdk.dir/src/base64.cpp.o -c /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/base64.cpp

CMakeFiles/edge_sdk.dir/src/base64.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edge_sdk.dir/src/base64.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/base64.cpp > CMakeFiles/edge_sdk.dir/src/base64.cpp.i

CMakeFiles/edge_sdk.dir/src/base64.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edge_sdk.dir/src/base64.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/base64.cpp -o CMakeFiles/edge_sdk.dir/src/base64.cpp.s

CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o: CMakeFiles/edge_sdk.dir/flags.make
CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o: ../src/edge_interface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o -c /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface.cpp

CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface.cpp > CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.i

CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface.cpp -o CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.s

CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o: CMakeFiles/edge_sdk.dir/flags.make
CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o: ../src/edge_interface_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o -c /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface_impl.cpp

CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface_impl.cpp > CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.i

CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/edge_interface_impl.cpp -o CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.s

CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o: CMakeFiles/edge_sdk.dir/flags.make
CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o: ../src/kafka_producer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o -c /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/kafka_producer.cpp

CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/kafka_producer.cpp > CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.i

CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/firefly/Documents/Seaway/SeawayEdgeSDK/src/kafka_producer.cpp -o CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.s

# Object files for target edge_sdk
edge_sdk_OBJECTS = \
"CMakeFiles/edge_sdk.dir/src/base64.cpp.o" \
"CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o" \
"CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o" \
"CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o"

# External object files for target edge_sdk
edge_sdk_EXTERNAL_OBJECTS =

../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/src/base64.cpp.o
../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/src/edge_interface.cpp.o
../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/src/edge_interface_impl.cpp.o
../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/src/kafka_producer.cpp.o
../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/build.make
../lib/libedge_sdk.so: ../3rd/jsoncpp/lib/libjsoncpp.so
../lib/libedge_sdk.so: ../3rd/mqtt/lib/libmosquitto.so
../lib/libedge_sdk.so: ../3rd/rdkafka/lib/librdkafka.so.1
../lib/libedge_sdk.so: ../3rd/rdkafka/lib/librdkafka++.so.1
../lib/libedge_sdk.so: CMakeFiles/edge_sdk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library ../lib/libedge_sdk.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/edge_sdk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edge_sdk.dir/build: ../lib/libedge_sdk.so

.PHONY : CMakeFiles/edge_sdk.dir/build

CMakeFiles/edge_sdk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/edge_sdk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/edge_sdk.dir/clean

CMakeFiles/edge_sdk.dir/depend:
	cd /home/firefly/Documents/Seaway/SeawayEdgeSDK/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/firefly/Documents/Seaway/SeawayEdgeSDK /home/firefly/Documents/Seaway/SeawayEdgeSDK /home/firefly/Documents/Seaway/SeawayEdgeSDK/build /home/firefly/Documents/Seaway/SeawayEdgeSDK/build /home/firefly/Documents/Seaway/SeawayEdgeSDK/build/CMakeFiles/edge_sdk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/edge_sdk.dir/depend

