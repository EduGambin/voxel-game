#ifndef GRAPHIC_HANDLER_HPP
#define GRAPHIC_HANDLER_HPP

#include <string>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Global.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#define GH_VERTEX_PATH "shaders/vertex.glsl"
#define GH_FRAGMENT_PATH "shaders/fragment.glsl"

class Graphic_handler
{
	private:
		// Shader program.
		Shader shader;
		// Holds the error info.
		std::string error_info;
		// Vertices to be drawn.
		std::vector<float> vertices;
		// Projection matrix.
		glm::mat4 projection_matrix;
		// Camera with the player's current view.
		// It's the link between the graphic handler and the input handler.
		Camera* camera;
		// Delta time shared among all handlers.
		float* delta_time;

	public:
		// Initializes the graphic handler. Should be called at the app initialization.
		// Returns 0 on success and -1 otherwise.
		int init(Camera* camera, float* delta_time);

		// Updates the matrixes.
		void update();

		// Getters and setters.
		std::string get_error_info() const;
};

#endif