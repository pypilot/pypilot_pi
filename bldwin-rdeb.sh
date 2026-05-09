#!/bin/bash

# FE2 Testplugin
# REKWITHDEBINFO VERSION
# Use "./build-win.sh" to run cmake.
# Adjust this command for your setup and Plugin.
# Requires wxWidgets setup
# - /home/fcgle/source/ocpn-wxWidgets
# - /home/fcgle/source/ where all the plugins and OpenCPN repos are kept.
# --------------------------------------
# For Opencpn using MS Visual Studio 2022
# --------------------------------------
# Used for local builds and testing.
# Create an empty "[plugin]/build" directory
# Use Bash Prompt from the [plugin] root directory: "bash ./bldwin-rdeb.sh"
# Find any errors in the build/output.txt file
# Then use bash prompt to run cloudsmith-upload.sh command: "bash ./bldwin-rdeb.sh"
# Which adds the metadata file to the tarball gz file.
# Set local environment to find and use wxWidgets

# Enable command tracing

set -x 

# Confirm build exists and empty it and if no build directory create it.

if [ -d "build" ]; then
    echo "The 'build' directory exists, remove all build dir files."
    rm -rf build/*
	
else
    echo "The 'build' directory does not exist. Create the build directory"
	mkdir build
fi

# wxWidgets settings 
set "wxDIR=C:\Users\fcgle\source\opencpn\..\ocpn_wxWidgets" 
set "wxWIN=C:\Users\fcgle\source\opencpn\..\ocpn_wxWidgets" 
set "wxWidgets_ROOT_DIR=C:\Users\fcgle\source\opencpn\..\ocpn_wxWidgets" 
set "wxWidgets_LIB_DIR=C:\Users\fcgle\source\opencpn\..\ocpn_wxWidgets\lib\vc_dll" 
set "VCver=17" 
set "VCstr=Visual Studio 17" 

# wxDIR=$WXWIN
# wxWidgets_ROOT_DIR=$WXWIN
# wxWidgets_LIB_DIR="$WXWIN/lib/vc14x_dll"
# WXWIN="/home/fcgle/source/wxWidgets-3.2.2"

# build the plugin with cmake

cd build
cmake -T v143 -A Win32 -DOCPN_TARGET=MSVC ..
cmake --build . --target package --config relwithdebinfo >output.txt
	
# Bash script completes tarball prep adding metadata into it.

bash ./cloudsmith-upload.sh

# Find ${bold}"build/output.txt"${normal} file if the build is not successful.
# Other examples below.
