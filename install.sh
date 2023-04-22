#!/bin/bash

# Update the package list and upgrade any existing packages
sudo apt update
sudo apt upgrade -y

# Install wxWidgets dependencies
sudo apt install -y build-essential libgtk-3-dev libjpeg-dev libpng-dev libtiff-dev \
libgtk2.0-dev libglu1-mesa-dev libnotify-dev freeglut3-dev libsm-dev libcanberra-gtk-module \
libwebkit2gtk-4.0-dev libssl-dev libcurl4-openssl-dev libexpat1-dev libbz2-dev liblzma-dev \
libarchive-dev libgstreamer-plugins-base1.0-dev

# Download and extract wxWidgets source code
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.2.1/wxWidgets-3.2.2.1.tar.bz2
tar -xf wxWidgets-3.2.2.1.tar.bz2
cd wxWidgets-3.2.2.1

# Configure and build wxWidgets
./configure --with-opengl --with-gtk=3
make -j4
sudo make install

# Clean up
cd ..
rm -rf wxWidgets-3.2.2.1 wxWidgets-3.2.2.1.tar.bz2

