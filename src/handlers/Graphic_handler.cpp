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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	return APP_SUCCESS;
}

void Graphic_handler::update()
{
	shader.use();
	shader.set_mat4("mvp", this->projection_matrix * this->camera->get_view_matrix());

	std::list<float> mesh = *this->camera->draw_data;
	float vertices[mesh.size()];
	int i = 0;
	for (std::list<float>::iterator it = mesh.begin(); it != mesh.end(); it++)
	{
		vertices[i++] = (*it);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, mesh.size());
}

void Graphic_handler::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

std::string Graphic_handler::get_error_info() const
{
	return this->error_info;
}