#include "handlers/Graphic_handler.hpp"

int Graphic_handler::init(Camera* camera, float* delta_time)
{
	if (shader.make_program(GH_VERTEX_PATH, GH_FRAGMENT_PATH))
	{
		this->error_info = shader.get_error_info();
		return APP_FAILURE;
	}

	if (camera == nullptr)
	{
		this->error_info = "The camera object cannot be a null pointer";
		return APP_FAILURE;
	}
	this->camera = camera;
	this->delta_time = delta_time;

	// Enabling the z-depth test.
	glEnable(GL_DEPTH_TEST);

	// Creating the projection matrix as it will be constant.
	this->projection_matrix = glm::perspective(APP_FOV, APP_ASPCET_RATIO, 0.1f, 100.0f);

	return APP_SUCCESS;
}

void Graphic_handler::update()
{
	
}

std::string Graphic_handler::get_error_info() const
{
	return this->error_info;
}