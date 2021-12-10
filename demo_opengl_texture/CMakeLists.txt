# // Copyright (c) 2021 huazheng
# // 
# // This software is released under the MIT License.
# // https://opensource.org/licenses/MIT

cmake_minimum_required(VERSION 3.10)

# set the project name and version.
project(learnopengl VERSION 0.1)

# include_directories(
#     "/usr/local/include"
# )

# make source file list.
list(APPEND C_SRCS glad.c main.cpp shader.cpp texture.cpp)

link_libraries(glfw3 GL X11 pthread Xrandr Xi dl m)

add_executable(demo ${C_SRCS})
