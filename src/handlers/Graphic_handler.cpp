#include "handlers/Graphic_handler.hpp"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

int Graphic_handler::init(Camera* camera, float* delta_time)
{
	if (shader.make_program(GH_VERTEX_PATH, GH_FRAGMENT_PATH))
	{
		this->error_info = shader.get_error_info();
		return APP_FAILURE;
	}
	shader.use();

	if (camera == nullptr)
	{
		this->error_info = "The camera object cannot be a null pointer";
		return APP_FAILURE;
	}
	this->camera = camera;
	this->delta_time = delta_time;

	// Enabling the z-depth test, face culling and antialiasing.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Creating the projection matrix as it will be constant.
	this->projection_matrix = glm::perspective(APP_FOV, APP_ASPCET_RATIO, 0.1f, 100.0f);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Loading textures flipped.
	stbi_set_flip_vertically_on_load(true);

	// Load the texture atlas.
	int width, height, channels;
	unsigned char* data = stbi_load("resources/textures.png", &width, &height, &channels,
		STBI_rgb);
	if (!data)
	{
		this->error_info = "Failed to load texture";
		return APP_FAILURE;
	}
	
	// Passing the image to the GPU.
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filter and mipmapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);

	return APP_SUCCESS;
}

void Graphic_handler::update()
{
	shader.set_mat4("mvp", this->projection_matrix * this->camera->get_view_matrix());
	std::list<float> mesh = *this->camera->draw_data;

	if (this->camera->is_data_modified)
	{
		float vertices[mesh.size()];
		int i = 0;
		for (std::list<float>::iterator it = mesh.begin(); it != mesh.end(); it++)
		{
			vertices[i++] = (*it);
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	glClearColor(0.529f, 0.808f, 0.98f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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