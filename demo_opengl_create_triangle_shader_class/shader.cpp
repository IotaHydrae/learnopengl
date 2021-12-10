// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file shader.cpp
 * @author hz (writeforever@foxmail.com)
 * @brief a shader class for 
 * @version 0.1
 * @date 2021-12-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    /* 1. reading glsl shader source code from file */
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "error failed to read file" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    /* 2. compile shaders */
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    /* error check */
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "error failed to compile vertex" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "error failed to compile fragment" << infoLog << std::endl;
    }

    /* 3. link the shader program */
    /**
	 * create a program object, the `glCreateProgram` 
	 * returns the ID of object.
	 */

	mID_shaderProgram = glCreateProgram();

    /**
	 * attach the shaders just created and link them.
	 * now you can call `glUseProgram(mID_shaderProgram)`
	 */
	glAttachShader(mID_shaderProgram, vertex);
	glAttachShader(mID_shaderProgram, fragment);
	glLinkProgram(mID_shaderProgram);

    /* TODO: error check for program link */
    glGetProgramiv(mID_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(mID_shaderProgram, 512, NULL, infoLog);
        std::cout << "program linking failed" << infoLog <<std::endl;
    }
    
	/* once we've linked program, these shaders no loger need anymore. */
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(mID_shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(mID_shaderProgram, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(mID_shaderProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(mID_shaderProgram, name.c_str()), value);
}
