#include <iostream>

#include "Application.hpp"

/* Camera our_camera; */

/* void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	our_camera.ProcessMouseMovement(xpos-lastX, lastY-ypos);
	lastX = xpos;
	lastY = ypos;
} */

int main()
{
	Application app;

	if (app.init())
	{
		std::cerr << "Failed to initialize the application" << std::endl;
		return -1;
	}
/* 
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
	glfwTerminate(); */
	app.run();
	app.destroy();
	return 0;
}