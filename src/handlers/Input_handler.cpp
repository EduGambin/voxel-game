#include "handlers/Input_handler.hpp"

// Auxiliar variables for the keyboard.
std::list<int> pressed_keys;

// Auxiliar variables for the mouse.
bool mouse_set = false;
double last_x, last_y;
double x_mov = 0.0;
double y_mov = 0.0;

int Input_handler::init(Camera* camera, float* delta_time)
{
	if (camera == nullptr)
	{
		this->error_info = "The camera object cannot be a null pointer";
		return APP_FAILURE;
	}
	this->camera = camera;
	this->delta_time = delta_time;

	return APP_SUCCESS;
}

void Input_handler::update()
{
	for (std::list<int>::iterator it = pressed_keys.begin(); it != pressed_keys.end(); it++)
	{
		switch ((*it))
		{
			case GLFW_KEY_W:
				camera->move(CAMERA_DIR_FORWARD, *this->delta_time);
				break;
			case GLFW_KEY_S:
				camera->move(CAMERA_DIR_BACKWARD, *this->delta_time);
				break;
			case GLFW_KEY_D:
				camera->move(CAMERA_DIR_RIGHT, *this->delta_time);
				break;
			case GLFW_KEY_A:
				camera->move(CAMERA_DIR_LEFT, *this->delta_time);
				break;
			default:
				break;
		}
	}

	this->camera->turn((float) x_mov, (float) y_mov);
}

void Input_handler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) 
	{
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
		else pressed_keys.push_back(key);
	}
	else if (action == GLFW_RELEASE)
	{
		pressed_keys.remove(key);
	}
}

void Input_handler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!mouse_set)
	{
		last_x = xpos;
		last_y = ypos;
	}
	else
	{
		x_mov = xpos - last_x;
		y_mov = last_y - ypos;
		last_x = xpos;
		last_y = ypos;
	}
}

void Input_handler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// TODO Implement the mouse button handling.
}

std::string Input_handler::get_error_info() const
{
	return this->error_info;
}