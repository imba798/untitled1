# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chenyl/CLionProjects/untitled1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chenyl/CLionProjects/untitled1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/untitled1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled1.dir/flags.make

CMakeFiles/untitled1.dir/main.cpp.o: CMakeFiles/untitled1.dir/flags.make
CMakeFiles/untitled1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenyl/CLionProjects/untitled1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled1.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled1.dir/main.cpp.o -c /home/chenyl/CLionProjects/untitled1/main.cpp

CMakeFiles/untitled1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chenyl/CLionProjects/untitled1/main.cpp > CMakeFiles/untitled1.dir/main.cpp.i

CMakeFiles/untitled1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chenyl/CLionProjects/untitled1/main.cpp -o CMakeFiles/untitled1.dir/main.cpp.s

CMakeFiles/untitled1.dir/detector.cpp.o: CMakeFiles/untitled1.dir/flags.make
CMakeFiles/untitled1.dir/detector.cpp.o: ../detector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenyl/CLionProjects/untitled1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/untitled1.dir/detector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled1.dir/detector.cpp.o -c /home/chenyl/CLionProjects/untitled1/detector.cpp

CMakeFiles/untitled1.dir/detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled1.dir/detector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chenyl/CLionProjects/untitled1/detector.cpp > CMakeFiles/untitled1.dir/detector.cpp.i

CMakeFiles/untitled1.dir/detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled1.dir/detector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chenyl/CLionProjects/untitled1/detector.cpp -o CMakeFiles/untitled1.dir/detector.cpp.s

# Object files for target untitled1
untitled1_OBJECTS = \
"CMakeFiles/untitled1.dir/main.cpp.o" \
"CMakeFiles/untitled1.dir/detector.cpp.o"

# External object files for target untitled1
untitled1_EXTERNAL_OBJECTS =

untitled1: CMakeFiles/untitled1.dir/main.cpp.o
untitled1: CMakeFiles/untitled1.dir/detector.cpp.o
untitled1: CMakeFiles/untitled1.dir/build.make
untitled1: /home/chenyl/opencv/build/lib/libopencv_gapi.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_stitching.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_aruco.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_barcode.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_bgsegm.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_bioinspired.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_ccalib.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_dnn_objdetect.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_dnn_superres.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_dpm.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_face.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_freetype.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_fuzzy.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_hfs.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_img_hash.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_intensity_transform.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_line_descriptor.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_mcc.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_quality.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_rapid.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_reg.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_rgbd.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_saliency.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_stereo.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_structured_light.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_superres.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_surface_matching.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_tracking.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_videostab.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_wechat_qrcode.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_xfeatures2d.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_xobjdetect.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_xphoto.so.4.5.3
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libtorch.so
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libc10.so
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libkineto.a
untitled1: /usr/local/cuda/lib64/stubs/libcuda.so
untitled1: /usr/local/cuda/lib64/libnvrtc.so
untitled1: /usr/local/cuda/lib64/libnvToolsExt.so
untitled1: /usr/local/cuda/lib64/libcudart.so
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libc10_cuda.so
untitled1: /home/chenyl/opencv/build/lib/libopencv_shape.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_highgui.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_datasets.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_plot.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_text.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_ml.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_phase_unwrapping.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_optflow.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_ximgproc.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_video.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_videoio.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_dnn.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_imgcodecs.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_objdetect.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_calib3d.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_features2d.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_flann.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_photo.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_imgproc.so.4.5.3
untitled1: /home/chenyl/opencv/build/lib/libopencv_core.so.4.5.3
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libc10_cuda.so
untitled1: /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch/lib/libc10.so
untitled1: /usr/local/cuda/lib64/libcufft.so
untitled1: /usr/local/cuda/lib64/libcurand.so
untitled1: /usr/local/cuda/lib64/libcublas.so
untitled1: /usr/local/cuda/lib64/libcudnn.so
untitled1: /usr/local/cuda/lib64/libnvToolsExt.so
untitled1: /usr/local/cuda/lib64/libcudart.so
untitled1: CMakeFiles/untitled1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chenyl/CLionProjects/untitled1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable untitled1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled1.dir/build: untitled1
.PHONY : CMakeFiles/untitled1.dir/build

CMakeFiles/untitled1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled1.dir/clean

CMakeFiles/untitled1.dir/depend:
	cd /home/chenyl/CLionProjects/untitled1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chenyl/CLionProjects/untitled1 /home/chenyl/CLionProjects/untitled1 /home/chenyl/CLionProjects/untitled1/cmake-build-debug /home/chenyl/CLionProjects/untitled1/cmake-build-debug /home/chenyl/CLionProjects/untitled1/cmake-build-debug/CMakeFiles/untitled1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/untitled1.dir/depend

