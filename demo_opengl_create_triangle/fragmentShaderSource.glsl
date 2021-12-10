// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(ourColor, 1.0);
} 