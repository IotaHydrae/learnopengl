#!/bin/bash

echo "Starting..."

echo "clean cache if exists..."

if [ -d "glad" ]; then
	echo "Removing dir glad"
	rm -rf glad
fi

if [ -d "glfw-3.3.5" ]; then
	echo "Removing dir glfw"
	rm -rf glfw-3.3.5
fi

echo "Install requirements..."


sudo apt install cmake libx11-dev \
    libgl-dev libxrandr-dev \
    libxinerama-dev libxcursor-dev \
    libxi-dev -y

unzip glad.zip -d glad

cd glad
sudo cp include/* -r /usr/local/include
cd -

unzip glfw-3.3.5.zip

cd glfw-3.3.5
mkdir build 
cd build
cmake ..
make -j8
sudo make install
cd ../..

if [ -d "glad" ]; then
	echo "Removing dir glad"
	rm -rf glad
fi

if [ -d "glfw-3.3.5" ]; then
	echo "Removing dir glfw"
	rm -rf glfw-3.3.5
fi

echo "Done."
exit 0
