// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef __SHADER_H
#define __SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    /* the program ID */
    unsigned int mID_shaderProgram;
    
    /* constructor reads and builds the shader */
    Shader(const char *vertexPath, const char *fragmentPath);
    /* use/active the shader */
    void use();
    /* unility uniform functions */
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif