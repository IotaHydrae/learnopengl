# learnopengl

## requirements

To build glfw, you need to install these libs:
```shell
sudo apt install cmake libx11-dev \
    libgl-dev libxrandr-dev \
    libxinerama-dev libxcursor-dev \
    libxi-dev -y
```
Then do:
```shell
# pretend the source code directory at ~/Downloads/glfw-xxx
# create a build dir
mkdir build && cd build && cmake ..
# build the glfw project
make -j8
# install the headers and libs
sudo make install
```

Also you need unzip the `glad.zip`, then 
copy the `include` dir to ex:`/usr/local/include`
and copy the `glad.c` which in `src` dir to your project.

The ldflags normally will be like this:
> -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

Finally, I advise you use cmake to build your project
which is really easy to be configured.
