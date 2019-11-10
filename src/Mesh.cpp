#include "Mesh.hpp"

Mesh::Mesh()
{
	this->chunks[0] = &basic_chunk;
	this->mesh_vertices = nullptr;
}

Mesh::~Mesh()
{
	delete this->mesh_vertices;
}

void Mesh::update()
{
	std::list<float> vertices;

	// Updating the mesh.
	for (unsigned int i = 0; i < MAX_CHUNKS_LOADED; i++)
	{
		if (chunks[i]->modified)
		{
			chunks[i]->modified = false;

			for (unsigned int j = 0; j < CHUNK_VOLUME; j++)
			{
				if (chunks[i]->blocks[j] == Block::AIR_BLOCK) continue;

				float x, y, z;
				Chunk::get_coords(x, y, z, j);
				if (chunks[i]->get_front_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> front_face = Block::front_face;
						vertices.push_back(front_face[k] + x);
						vertices.push_back(front_face[k+1] + y);
						vertices.push_back(front_face[k+2] + z);
					}
				}

				if (chunks[i]->get_back_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> back_face = Block::back_face;
						vertices.push_back(back_face[k] + x);
						vertices.push_back(back_face[k+1] + y);
						vertices.push_back(back_face[k+2] + z);
					}
				}

				if (chunks[i]->get_up_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> up_face = Block::up_face;
						vertices.push_back(up_face[k] + x);
						vertices.push_back(up_face[k+1] + y);
						vertices.push_back(up_face[k+2] + z);
					}
				}

				if (chunks[i]->get_down_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> down_face = Block::down_face;
						vertices.push_back(down_face[k] + x);
						vertices.push_back(down_face[k+1] + y);
						vertices.push_back(down_face[k+2] + z);
					}
				}

				if (chunks[i]->get_left_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> left_face = Block::left_face;
						vertices.push_back(left_face[k] + x);
						vertices.push_back(left_face[k+1] + y);
						vertices.push_back(left_face[k+2] + z);
					}
				}

				if (chunks[i]->get_right_block(j) == Block::AIR_BLOCK)
				{
					for(unsigned int k = 0; k < Block::VERTICES_PER_FACE; k += 3)
					{
						std::array<const float, Block::VERTICES_PER_FACE> right_face = Block::right_face;
						vertices.push_back(right_face[k] + x);
						vertices.push_back(right_face[k+1] + y);
						vertices.push_back(right_face[k+2] + z);
					}
				}
			}
		}
	}
	this->vertices_count = vertices.size() / 3;
	float algo[vertices.size()];

	// Putting the vertices into an array.
	if (this->mesh_vertices != nullptr) delete mesh_vertices;
	this->mesh_vertices = new float[vertices.size()];

	int i = 0;
	for (std::list<float>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		algo[i++] = (*it);
	}

	for (i = 0; i < 18; i+=3)
	{
		std::cout << "(" << mesh_vertices[i] << "," << mesh_vertices[i+1] << "," << mesh_vertices[i+2] << ")" << std::endl;
	}

	// Deleting the old vertex objects.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	// Creating new vertex objects.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(algo), algo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Mesh::clean()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

unsigned int Mesh::get_vertices_count() const
{
	return this->vertices_count;
}