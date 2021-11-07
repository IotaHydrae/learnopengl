#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
}

int main(int argc, char **argv)
{
	printf("Hello, World!\n");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
	if(window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	glViewport(0,0,800,600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* render loop */
	while(!glfwWindowShouldClose(window))
	{
		/* process input event */
		processInput(window);

		/* rendering commands here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* check and call events and swap the buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
