#!/bin/bash


#######################################################################################
#                                                                                     #
# Check out appimage static runtime so fuse2 is no longer needed.                     #
# https://github.com/endless-sky/endless-sky/blob/v0.10.5/utils/build_appimage.sh#L27 #
#                                                                                     #
#######################################################################################


# Check if the build directory is provided
if [ "$#" -lt 1 ]; then
        echo "Usage: ${0##*/} <build_directory>"
        exit 1
fi
build_dir=$(realpath "$1")

# Navigate to the scripts directory
cd "${0%/*}"

# build and install
cmake --build "$build_dir" --config Release
cmake --install "$build_dir" --prefix "$build_dir/AppDir/usr"

# set runpath
patchelf --set-rpath "$build_dir/vcpkg_installed/x64-linux-dynamic/lib" "$build_dir/AppDir/usr/bin/ricochet"

# dl appimage maker
wget -nc -q -O "$build_dir/linuxdeploy" "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage" && chmod +x "$build_dir/linuxdeploy"

# make appimage
LDAI_OUTPUT="$build_dir/Ricochet-x86_64.AppImage" "$build_dir/linuxdeploy" --appdir "$build_dir/AppDir" -e "$build_dir/AppDir/usr/bin/ricochet" -d "$build_dir/AppDir/usr/share/applications/ricochet.desktop" -i "$build_dir/AppDir/usr/share/icons/hicolor/256x256/apps/ricochet.png" --output appimage
