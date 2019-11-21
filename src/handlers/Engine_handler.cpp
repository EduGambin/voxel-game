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
	this->chunks[1] = new Chunk();

	Chunk* brothers_0[] = {nullptr, nullptr, nullptr, nullptr, nullptr, this->chunks[1]};
	Chunk* brothers_1[] = {nullptr, nullptr, nullptr, nullptr, this->chunks[0], nullptr};

	this->chunks[0]->init(0, 0, 0, brothers_0);
	this->chunks[1]->init(1, 0, 0, brothers_1);

	return APP_SUCCESS;
}

void Engine_handler::update()
{
	bool mesh_modified = false;
	for (unsigned int i = 0u; i < this->chunks.size(); i++)
	{
		if (this->chunks[i]->modified)
		{
			// Removing the deleted data.
			if (this->chunks[i]->removed_data.second != 0u)
			{
				for (std::list<float>::iterator it = this->mesh.begin(); it != this->mesh.end(); it++)
				{
					if ((*it) == this->chunks[i]->removed_data.first)
					{
						// Once we find the first element to be removed, we remove all.
						for (int j = 0; j < this->chunks[i]->removed_data.second; j++)
							this->mesh.erase(it++);
						break;
					}
				}
				this->chunks[i]->removed_data.second = 0u;
			}

			// Adding the new data.
			if (!this->chunks[i]->added_data.empty())
			{
				for (std::list<float>::iterator it = this->chunks[i]->added_data.begin(); it != this->chunks[i]->added_data.end(); it++)
				{
					this->mesh.emplace_back(*it);
				}
				this->chunks[i]->added_data.clear();
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