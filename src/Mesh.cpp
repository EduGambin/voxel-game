#include "Mesh.hpp"

Mesh::Mesh()
{
	chunks[0] = &basic_chunk;
	mesh_vertices = nullptr;
	vao = -1;
	vbo = -1;
}

Mesh::~Mesh()
{
	delete mesh_vertices;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Mesh::loadVertices()
{
	std::list<float> vertices;

	// Updating the mesh.
	for (int i = 0; i < MAX_CHUNKS_LOADED; i++)
	{
		if (chunks[i]->modified)
		{
			chunks[i]->modified = false;
			for (int j = 0; j < CHUNK_VOLUME; j++)
			{
				if (chunks[i]->blocks[j] == BLOCK_AIR) break;

				float x, y, z;
				Chunk::get_coords(x, y, z, j);

				if (chunks[i]->get_front_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> front_face = Block::front_face;
						vertices.push_back(front_face[k] + x);
						vertices.push_back(front_face[k+1] + y);
						vertices.push_back(front_face[k+2] + z);
					}
				}

				if (chunks[i]->get_back_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> back_face = Block::back_face;
						vertices.push_back(back_face[k] + x);
						vertices.push_back(back_face[k+1] + y);
						vertices.push_back(back_face[k+2] + z);
					}
				}

				if (chunks[i]->get_up_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> up_face = Block::up_face;
						vertices.push_back(up_face[k] + x);
						vertices.push_back(up_face[k+1] + y);
						vertices.push_back(up_face[k+2] + z);
					}
				}

				if (chunks[i]->get_down_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> down_face = Block::down_face;
						vertices.push_back(down_face[k] + x);
						vertices.push_back(down_face[k+1] + y);
						vertices.push_back(down_face[k+2] + z);
					}
				}

				if (chunks[i]->get_left_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> left_face = Block::left_face;
						vertices.push_back(left_face[k] + x);
						vertices.push_back(left_face[k+1] + y);
						vertices.push_back(left_face[k+2] + z);
					}
				}

				if (chunks[i]->get_right_block(j) == BLOCK_AIR)
				{
					for(int k = 0; k < VERT_PER_FACE; i += 3)
					{
						std::array<const float, VERT_PER_FACE> right_face = Block::right_face;
						vertices.push_back(right_face[k] + x);
						vertices.push_back(right_face[k+1] + y);
						vertices.push_back(right_face[k+2] + z);
					}
				}
			}
		}
	}

	// Putting the vertices into an array.
	if (mesh_vertices != nullptr) delete mesh_vertices;
	mesh_vertices = new float[vertices.size()];

	int i = 0;
	for (std::list<float>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		mesh_vertices[i++] = (*it);
	}

	// Creating a VAO and a VBO.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_vertices), mesh_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}