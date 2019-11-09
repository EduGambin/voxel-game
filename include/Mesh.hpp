#ifndef MESH_HPP
#define MESH_HPP

#include <list>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Chunk.hpp"

#define	MAX_CHUNKS_LOADED 1

class Mesh
{
	private:
		float* mesh_vertices;
		unsigned int vao, vbo;
		Chunk* chunks[MAX_CHUNKS_LOADED];

	public:
		Chunk basic_chunk;
		
		Mesh();
		~Mesh();
		void loadVertices();

		unsigned int get_vertices_count()
		{
			return sizeof(mesh_vertices);
		}
};

#endif