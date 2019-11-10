#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

float lastX = 0.0f;
float lastY = 0.0f;

Camera our_camera;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	our_camera.ProcessMouseMovement(xpos-lastX, lastY-ypos);
	lastX = xpos;
	lastY = ypos;
}

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

	Shader our_shader;
	if (our_shader.make_program("shaders/vertex.glsl", "shaders/fragment.glsl") == -1)
	{
		std::cerr << our_shader.get_info() << std::endl;
		return -1;
	}
	our_shader.use();

	// Enabling the depth test.
	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPosCallback(window, mouse_callback);

	Mesh m;
	m.update();

	// Matrixes and defining the projection one.
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	int modelLoc = glGetUniformLocation(our_shader.get_id(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	projection = glm::perspective(glm::radians(45.0f), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);
	modelLoc = glGetUniformLocation(our_shader.get_id(), "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		// Cleaning the screen.
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			our_camera.ProcessKeyboard(FORWARD, 0.166f);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			our_camera.ProcessKeyboard(BACKWARD, 0.166f);

		our_camera.ProcessMouseMovement(0.0f, 0.0f);
		view = our_camera.GetViewMatrix();

		// Sending to the video card.
		modelLoc = glGetUniformLocation(our_shader.get_id(), "view");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		// Drawing.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, m.get_vertices_count());

		// Presenting the graphics.
		glfwSwapBuffers(window);
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	m.clean();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}