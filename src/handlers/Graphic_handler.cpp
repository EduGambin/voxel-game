#include "handlers/Graphic_handler.hpp"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

const float screen_quad[] = {
	// Vectors		// Texture
	-1.0f,  1.0f,	0.0f, 1.0f,
	-1.0f, -1.0f,	0.0f, 0.0f,
	 1.0f, -1.0f,	1.0f, 0.0f,

    -1.0f,  1.0f,	0.0f, 1.0f,
     1.0f, -1.0f,	1.0f, 0.0f,
     1.0f,  1.0f,	1.0f, 1.0f
};

int Graphic_handler::init(Camera* camera, float* delta_time)
{
	if (shader.make_program(GH_VERTEX_PATH, GH_FRAGMENT_PATH))
	{
		this->error_info = shader.get_error_info();
		return APP_FAILURE;
	}

	if (screen_shader.make_program(GH_FB_VERTEX_PATH, GH_FB_FRAGMENT_PATH))
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

	// Creating the projection matrix as it will be constant.
	this->projection_matrix = glm::perspective(APP_FOV, APP_ASPCET_RATIO, 0.1f, 100.0f);

	// Generating vertex objects.
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	// Generating and configuring framebuffer.
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if(!glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		this->error_info = "Failed to complete a framebuffer";
		return APP_FAILURE;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
	shader.use();
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Texture wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filter and mipmapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
	shader.remove();
	return APP_SUCCESS;
}

void Graphic_handler::update()
{
	// Drawing to the framebuffer.
	shader.use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClearColor(0.529f, 0.808f, 0.98f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enabling the z-depth test, face culling and antialiasing.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Drawing.
	glDrawArrays(GL_TRIANGLES, 0, mesh.size());
	shader.remove();


	// Drawing the actual framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphic_handler::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteFramebuffers(1, &fbo);
}

std::string Graphic_handler::get_error_info() const
{
	return this->error_info;
}