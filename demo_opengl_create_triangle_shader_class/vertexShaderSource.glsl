// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 ourPos;
uniform vec4 offset;

void main()
{
    gl_Position = vec4(aPos.x+offset.x, -aPos.y+offset.y, aPos.z+offset.z, 1.0);
    ourColor = aColor;
    ourPos = aPos;
}
