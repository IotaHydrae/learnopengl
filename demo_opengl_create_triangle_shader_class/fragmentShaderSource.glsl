// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 330 core
out vec4 fragColor;
in vec3 ourColor;
in vec3 ourPos;

void main()
{
  fragColor = vec4(ourPos, 1.0);

}
