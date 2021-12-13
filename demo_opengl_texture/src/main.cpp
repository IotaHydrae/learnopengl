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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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
	unsigned int EBO;

	/* a coord array of `xyz` for triangle */
	float vertices[] = {
		//positions			//colors		  //texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 0, 3
	};


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	/* generate a vertex buffer object with a ID */
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	/* bind this VBO type to `GL_ARRAY_BUFFER` */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* copy the previously defined vertex data into the buffer's memory */
	/* `GL_STATIC_DRAW` because the data filled in that nerver changed */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	/* do the same as top */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* set the vertex attributes pointers for positions */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	/* set color attributes */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* set texture coords attributes */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	/* load,compile,link the glsl source */
    Shader ourShader("../vertexShaderSource.glsl", "../fragmentShaderSource.glsl");
	ourShader.use();
	
	unsigned int texture1, texture2;
	/* number of texture objects to be generated. */
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	/* texture settings */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* load texture used by `stb_image.h` */
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("../assets/container.jpg", &width, &height, &nrChannels, 0);
	if(data)
	{
		/* `glGenTextures` also could revice a array and sizeof it. */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Faield to load texture " << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	data = stbi_load("../assets/awesomeface.png", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture2", 1);

	/* the render loop */
	while (!glfwWindowShouldClose(window))
	{
		/* process input event */
		processInput(window);

		/* rendering commands here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		/* active the shader */
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* check and call events and swap the buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/* de-allocate all resources onclude they're outlived their purpose */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	/* clearing all previously allocated GLFW resources. */
	glfwTerminate();

    return 0;
}
