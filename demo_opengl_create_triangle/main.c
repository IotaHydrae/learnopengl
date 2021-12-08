#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLSL_FILE_LENGTH 4096

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

	unsigned int VAO;
	unsigned int VBO;
	/* a coord array of `xyz` for triangle */
	float vertices[] = {
		//positions			//colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
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

	/* basic vertex shader in GLSL(could read from file) */
	char vertexShaderSource_r[GLSL_FILE_LENGTH];
	const char *vertexShaderSource = vertexShaderSource_r;
	FILE *fp_vertexShaderSource = fopen("../vertexShaderSource.glsl", "r");
	if (!fp_vertexShaderSource)
	{
		printf("open file failed exiting...");
		return -1;
	}
	fread(&vertexShaderSource_r, sizeof(char), GLSL_FILE_LENGTH, fp_vertexShaderSource);
	fclose(fp_vertexShaderSource);
	// printf("shaders code:\n%s\n", vertexShaderSource_r);

	/* compiling a shader */
	/* create a shader */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	/* attach the shader source code to the shader object and compile the shader. */
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/* TODO:error check of shader compiling here. */
	int succss;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succss);
	if (!succss)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR: SHADER vertex compile failed!\n");
	}

	/**
     * `fragment shader` the second step to render a triangle.
     * the fragment shader is all about calculating the color
     * output of your pixels.
     */
	/* do the same thing with vertexShaderSource */
	// const char *fragmentShaderSource = "#version 330 core\n"
	// 	"out vec4 FragColor;\n"
	// 	"void main()\n"
	// 	"{\n"
	// 	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
	// 	"}\0";

	/* read fragment shader code from file */
	char fragmentShaderSource_r[GLSL_FILE_LENGTH];
	const char *fragmentShaderSource = fragmentShaderSource_r;
	FILE *fp_fragmentShaderSource = fopen("../fragmentShaderSource.glsl", "r");
	if (!fp_fragmentShaderSource)
	{
		printf("open file failed exiting...");
		return -1;
	}
	fread(&fragmentShaderSource_r, sizeof(char), GLSL_FILE_LENGTH, fp_fragmentShaderSource);
	fclose(fp_fragmentShaderSource);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* error check for fragment shader code compile. */
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succss);
	if (!succss)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR: SHADER fragmentShader compile failed!\n");
	}

	/**
	 * create a program object, the `glCreateProgram` 
	 * returns the ID of object.
	 */
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	/**
	 * attach the shaders just created and link them.
	 * now you can call `glUseProgram(shaderProgram)`
	 */
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* TODO: error check for program link */

	/* once we've linked program, these shaders no loger need anymore. */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/**
	 * a way to pass data from cpu to gpu
	 * uses `uniform`
	 */


	/* the render loop */
	while (!glfwWindowShouldClose(window))
	{
		/* process input event */
		processInput(window);

		/* rendering commands here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* active the shader */
		glUseProgram(shaderProgram);
		
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
