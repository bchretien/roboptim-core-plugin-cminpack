#!/bin/sh
set -e

# Directories.
root_dir=`pwd`
build_dir="$root_dir/_travis/build"
install_dir="$root_dir/_travis/install"
core_dir="$build_dir/roboptim-core"

# Shortcuts.
git_clone="git clone --quiet --recursive"

# Create layout.
rm -rf "$build_dir" "$install_dir"
mkdir -p "$build_dir"
mkdir -p "$install_dir"

# Setup environment variables.
export LD_LIBRARY_PATH="$install_dir/lib:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="$install_dir/lib/roboptim-core:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$install_dir/lib/pkgconfig:$PKG_CONFIG_PATH"

# Checkout roboptim-core
echo "Installing dependencies..."
cd "$build_dir"
$git_clone "git://github.com/roboptim/roboptim-core.git"
cd "$core_dir"
cmake . -DCMAKE_INSTALL_PREFIX:STRING="$install_dir"
make install

# Build package
echo "Building package..."
cd "$build_dir"
cmake "$root_dir" -DCMAKE_INSTALL_PREFIX="$install_dir"
make
make install
$root_dir/tests/wrap.py
$root_dir/tests/function.py
make test