#ifndef GRAPHIC_HANDLER_HPP
#define GRAPHIC_HANDLER_HPP

#include <string>
#include <list>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Global.hpp"
#include "graphics/Shader.hpp"
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
		// Projection matrix.
		glm::mat4 projection_matrix;
		// Camera with the player's current view.
		// Link between handlers.
		Camera* camera;
		// Delta time shared among all handlers.
		float* delta_time;

		// OpenGL vertex objects.
		unsigned int vao, vbo;

		// Texture atlas with all the existing textures.
		unsigned int texture;

	public:
		// Initializes the graphic handler. Should be called at the app initialization.
		// Returns APP_SUCCESS on success and APP_FAILURE otherwise.
		int init(Camera* camera, float* delta_time);

		// Updates the matrixes.
		void update();

		// Destroys all the created objects. Should be called at the end.
		void destroy();

		// Getters and setters.
		std::string get_error_info() const;
};

#endif