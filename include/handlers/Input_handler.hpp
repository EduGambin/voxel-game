#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <list>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Global.hpp"
#include "Camera.hpp"

class Input_handler
{
	private:
		std::string error_info;
		// Camera with the player's current view.
		// It's the link between the graphic handler and the input handler.
		Camera* camera;
		// Delta time shared among all handlers.
		float* delta_time;

	public:
		// Initializes the graphic handler. Should be called at the app initialization.
		// Returns 0 on success and -1 otherwise.
		int init(Camera* camera, float* delta_time);

		// Updates everything according to the user's input.
		void update();

		// Static functions called when certain input events happen.
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		// Getters and setters.
		std::string get_error_info() const;
};

#endif