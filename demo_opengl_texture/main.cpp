// Copyright (c) 2021 huazheng
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file test.cpp
 * @author huazheng (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shader.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define GLSL_FILE_LENGTH 4096
#define DEBUG_INFO

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		;
}

int main(int argc, char **argv)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VAO;	/* vertex array object */
	unsigned int VBO;	/* vertex buffer object */

	/* a coord array of `xyz` for triangle */
	float vertices[] = {
		//positions			//colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	float texCoords[] = {
		0.0f, 0.0f,	/* lower-left corner */
		1.0f, 0.0f, /* lower-right corner */
		0.5f, 1.0f, /* top-center corner */
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	/* generate a vertex buffer object with a ID */
	glGenBuffers(1, &VBO);

	/* bind this VBO type to `GL_ARRAY_BUFFER` */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* copy the previously defined vertex data into the buffer's memory */
	/* `GL_STATIC_DRAW` because the data filled in that nerver changed */
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* set the vertex attributes pointers for positions */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	/* set color attributes */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* load,compile,link the glsl source */
    Shader ourShader("../vertexShaderSource.glsl", "../fragmentShaderSource.glsl");

	/* texture settings */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	/* `glGenTextures` also could revice a array and sizeof it. */
	unsigned int texture;
	glGenTextures(1, &texture);
	
	glBindTexture
    
	/* the render loop */
	while (!glfwWindowShouldClose(window))
	{
		/* process input event */
		processInput(window);

		/* rendering commands here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* active the shader */
		ourShader.use();
        // ourShader.setFloat("someUniform", 1.0f);
		
		/* update the color of triangle dynamically */
		// float timeValue = glfwGetTime();
		// float greenValue = (sin(timeValue)/2.0f)+0.5f;
		// int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* check and call events and swap the buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}