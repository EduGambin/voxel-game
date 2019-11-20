#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Global.hpp"
#include "Camera.hpp"
#include "handlers/Input_handler.hpp"
#include "handlers/Engine_handler.hpp"
#include "handlers/Graphic_handler.hpp"

class Application
{
	private:
		GLFWwindow* window;
		Input_handler ih;
		Engine_handler eh;	// Needs to be initialized.
		Graphic_handler gh;	// Needs to be initialized.
		Camera camera;		// Needs to be initialized.

		float delta_time;

		// Callback funtion in case an error occurs.
		static void error_callback(int error, const char* description);
		// Callback function when a key is pressed.
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		// Callback function when the mouse is moved.
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		// Callback function when a mouse button is pressed.
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	public:
		// Initializes the app. Should be called before doing anything else.
		// Returns APP_SUCESS on sucess and APP_FAILURE on failure.
		int init();
		// Destroys and cleans everything. Should be called at the end of the program.
		void destroy();

		// Executes the main application loop.
		void run();
};

#endif