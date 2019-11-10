#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <list>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Chunk.hpp"

#define	MAX_CHUNKS_LOADED 1

class Mesh
{
	private:
		// Array of vertices to be drawn.
		float* mesh_vertices;
		// Vertex array and buffer objects.
		unsigned int vao, vbo;
		// Array of chunks to check.
		Chunk* chunks[MAX_CHUNKS_LOADED];
		// Holds the number of vertices drawn.
		unsigned int vertices_count;

		Chunk basic_chunk;	// For testing purposes.

	public:
		// Constructor and destructor.
		Mesh();
		~Mesh();

		// Updates the mesh with the modified chunks.
		void update();
		// Cleans all the vertex data.
		void clean();
		// Return the number of vertices to be drawn.
		unsigned int get_vertices_count() const;
};

#endif