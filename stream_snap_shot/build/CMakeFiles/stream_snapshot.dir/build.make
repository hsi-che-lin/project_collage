# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build"

# Include any dependencies generated for this target.
include CMakeFiles/stream_snapshot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stream_snapshot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stream_snapshot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stream_snapshot.dir/flags.make

CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj: CMakeFiles/stream_snapshot.dir/flags.make
CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj: CMakeFiles/stream_snapshot.dir/includes_CXX.rsp
CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj: ../stream_snapshot.cpp
CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj: CMakeFiles/stream_snapshot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj -MF CMakeFiles\stream_snapshot.dir\stream_snapshot.cpp.obj.d -o CMakeFiles\stream_snapshot.dir\stream_snapshot.cpp.obj -c "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\stream_snapshot.cpp"

CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\stream_snapshot.cpp" > CMakeFiles\stream_snapshot.dir\stream_snapshot.cpp.i

CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\stream_snapshot.cpp" -o CMakeFiles\stream_snapshot.dir\stream_snapshot.cpp.s

# Object files for target stream_snapshot
stream_snapshot_OBJECTS = \
"CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj"

# External object files for target stream_snapshot
stream_snapshot_EXTERNAL_OBJECTS =

stream_snapshot.exe: CMakeFiles/stream_snapshot.dir/stream_snapshot.cpp.obj
stream_snapshot.exe: CMakeFiles/stream_snapshot.dir/build.make
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_highgui452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_ml452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_objdetect452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_photo452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_stitching452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_video452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_videoio452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_imgcodecs452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_calib3d452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_dnn452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_features2d452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_flann452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_imgproc452.dll.a
stream_snapshot.exe: C:/Users/HSI-CHE\ LIN/AppData/Local/opencv/install/x64/mingw/lib/libopencv_core452.dll.a
stream_snapshot.exe: CMakeFiles/stream_snapshot.dir/linklibs.rsp
stream_snapshot.exe: CMakeFiles/stream_snapshot.dir/objects1.rsp
stream_snapshot.exe: CMakeFiles/stream_snapshot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stream_snapshot.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\stream_snapshot.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stream_snapshot.dir/build: stream_snapshot.exe
.PHONY : CMakeFiles/stream_snapshot.dir/build

CMakeFiles/stream_snapshot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\stream_snapshot.dir\cmake_clean.cmake
.PHONY : CMakeFiles/stream_snapshot.dir/clean

CMakeFiles/stream_snapshot.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot" "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot" "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build" "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build" "C:\Users\HSI-CHE LIN\start\project\collage\code\stream_snap_shot\build\CMakeFiles\stream_snapshot.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/stream_snapshot.dir/depend

