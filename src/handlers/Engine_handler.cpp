#include "handlers/Engine_handler.hpp"

int Engine_handler::init(Camera* camera, float* delta_time)
{
	if (camera == nullptr)
	{
		this->error_info = "The camera object cannot be a null pointer";
		return APP_FAILURE;
	}
	this->camera = camera;
	this->delta_time = delta_time;

	this->chunks[0] = new Chunk();

	return APP_SUCCESS;
}

void Engine_handler::update()
{
	for (unsigned int i = 0; i < this->chunks.size(); i++) 
	{
		if (this->chunks[i]->modified)
		{
			// Removing the deleted data.
			if (this->chunks[i]->removed_data.second != 0)
			{
				for (std::list<float>::iterator it = mesh.begin(); it != mesh.end(); it++)
				{
					if ((*it) == this->chunks[i]->removed_data.first)
					{
						for (unsigned int j = 0; j < this->chunks[i]->removed_data.second; j++)
							mesh.erase(it++);
						break;
					}
				}
			}

			// Adding the new data.
			if (!this->chunks[i]->added_vertices.empty())
			{
				std::list<float> new_ver = this->chunks[i]->added_vertices;
				for (std::list<float>::iterator it = new_ver.begin(); it != new_ver.end(); it++)
					mesh.push_back((*it));
			}
		}
		this->chunks[i]->modified = false;
	}
	this->camera->draw_data = &this->mesh;
}

void Engine_handler::destroy()
{
	for (unsigned int i = 0; i < this->chunks.size(); i++) delete this->chunks[i];
}

std::string Engine_handler::get_error_info() const
{
	return this->error_info;
}