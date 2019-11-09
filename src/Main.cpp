#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Mesh.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
	// Initializing GLFW.
	glfwInit();

	// Setting the OpenGL version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setting the window options.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	// Creating the window.
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initializing GLAD.
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	Mesh m;
	m.loadVertices();

	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		// Cleaning the screen.
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Drawing.
		glDrawArrays(GL_TRIANGLES, 0, m.get_vertices_count());

		// Presenting the graphics.
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}