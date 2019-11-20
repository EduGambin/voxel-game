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
	bool mesh_modified = false;
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
			if (!this->chunks[i]->added_vertices.empty() && !this->chunks[i]->added_vertices.empty())
			{
				std::list<float> new_ver = this->chunks[i]->added_vertices;
				std::list<float> new_uvs = this->chunks[i]->added_uvs;

				std::list<float>::iterator it1 = new_ver.begin();
				std::list<float>::iterator it2 = new_uvs.begin();

				for (it1 = new_ver.begin(); it1 != new_ver.end(); /* Not needed */)
				{
					// New vertice.
					mesh.push_back((*(it1++)));
					mesh.push_back((*(it1++)));
					mesh.push_back((*(it1++)));

					// New uv.
					mesh.push_back((*(it2++)));
					mesh.push_back((*(it2++)));
				}
			}
			this->chunks[i]->modified = false;
			mesh_modified = true;	
		}
	}
	if (mesh_modified)
	{
		this->camera->is_data_modified = true;
		this->camera->draw_data = &this->mesh;
	}
	else
		this->camera->is_data_modified = false;
}

void Engine_handler::destroy()
{
	for (unsigned int i = 0; i < this->chunks.size(); i++) delete this->chunks[i];
}

std::string Engine_handler::get_error_info() const
{
	return this->error_info;
}