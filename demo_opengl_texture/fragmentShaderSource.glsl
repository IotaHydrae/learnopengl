// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#version 330 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
  // fragColor = texture(texture1, TexCoord) * vec4(ourColor,1.0);
  fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
