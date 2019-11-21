#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <array>
#include <list>
#include <utility>

#include "Global.hpp"

#define CHUNK_LENGTH 	  16
#define CHUNK_AREA 		 256
#define CHUNK_VOLUME 	4096

#define BLOCK_VPF 	18
#define BLOCK_UVPF	12
#define BLOCK_AIR 	 0
#define BLOCK_GRASS  1
#define BLOCK_DIRT	 2

#define BLOCK_FRONT_FACE_BIT 	 1	// 000001
#define BLOCK_BACK_FACE_BIT 	 2	// 000010
#define BLOCK_UP_FACE_BIT		 4	// 000100
#define BLOCK_DOWN_FACE_BIT 	 8	// 001000
#define BLOCK_LEFT_FACE_BIT 	16	// 010000
#define BLOCK_RIGHT_FACE_BIT 	32	// 100000

#define TEXTURE_LENGTH 			16.0f
#define TEXTURE_ATLAS_WIDTH 	64.0f
#define TEXTURE_ATLAS_HEIGHT	32.0f

namespace Block 
{
	const std::array<const float, BLOCK_VPF> front_face =
	{
		// First triangle.
		0.0f, 0.0f, 0.0f,	// Left-bottom-front.
		1.0f, 0.0f, 0.0f,	// Right-bottom-front.
		1.0f, 1.0f, 0.0f,	// Right-top_front.

		// Second triangle.
		1.0f, 1.0f, 0.0f,	// Right-top_front.
		0.0f, 1.0f, 0.0f,	// Left-top_front.
		0.0f, 0.0f, 0.0f,	// Left-bottom-front.
	};

	const std::array<const float, BLOCK_VPF> back_face =
	{
		// First triangle.
		1.0f, 0.0f, -1.0f,	// Right-bottom-back.
		0.0f, 0.0f, -1.0f,	// Left-bottom-back.
		0.0f, 1.0f, -1.0f,	// Left-top-back.

		// Second triangle.
		0.0f, 1.0f, -1.0f,	// Left-top-back.
		1.0f, 1.0f, -1.0f,	// Right-top-back.
		1.0f, 0.0f, -1.0f,	// Right-bottom-back.
	};

	const std::array<const float, BLOCK_VPF> up_face =
	{
		// First triangle.
		0.0f, 1.0f,  0.0f,	// Left-top_front.
		1.0f, 1.0f,  0.0f,	// Right-top_front.
		1.0f, 1.0f, -1.0f,	// Right-top-back.

		// Second triangle.
		1.0f, 1.0f, -1.0f,	// Right-top-back.
		0.0f, 1.0f, -1.0f,	// Left-top-back.
		0.0f, 1.0f,  0.0f,	// Left-top_front.
	};

	const std::array<const float, BLOCK_VPF> down_face =
	{
		// First triangle.
		0.0f, 0.0f, -1.0f,	// Left-bottom-back.
		1.0f, 0.0f, -1.0f,	// Right-bottom-back.
		1.0f, 0.0f,  0.0f,	// Right-bottom-front.

		// Second triangle.
		1.0f, 0.0f,  0.0f,	// Right-bottom-front.
		0.0f, 0.0f,  0.0f,	// Left-bottom-front.
		0.0f, 0.0f, -1.0f,	// Left-bottom-back.
	};

	const std::array<const float, BLOCK_VPF> left_face =
	{
		// First triangle.
		0.0f, 0.0f, -1.0f,	// Left-bottom-back.
		0.0f, 0.0f,  0.0f,	// Left-bottom-front.
		0.0f, 1.0f,  0.0f,	// Left-top_front.

		// Second triangle.
		0.0f, 1.0f,  0.0f,	// Left-top_front.
		0.0f, 1.0f, -1.0f,	// Left-top-back.
		0.0f, 0.0f, -1.0f,	// Left-bottom-back.
	};

	const std::array<const float, BLOCK_VPF> right_face =
	{
		// First triangle.
		1.0f, 0.0f,  0.0f,	// Right-bottom-front.
		1.0f, 0.0f, -1.0f,	// Right-bottom-back.
		1.0f, 1.0f, -1.0f,	// Right-top-back.

		// Second triangle.
		1.0f, 1.0f, -1.0f,	// Right-top-back.
		1.0f, 1.0f,  0.0f,	// Right-top_front.
		1.0f, 0.0f,  0.0f,	// Right-bottom-front.
	};

};

class Chunk
{
	private:
		// Position of the chunk in the world.
		unsigned int x, y, z;

		// NOTA //
		// Añadir un contador de vértices y un contador de uv's para poder hacer los accesos
		// en diferente orden.

		// Adding the vertices sepcified by the bits and the coordinates.
		void add_vertices(int face_bits, float x, float y, float z);
		// Adding the uv coordinates of a given face and a certain block.
		void add_uvs(int face_bits, unsigned int block_type);
		// Load all the just created data to the added data.
		void load_data();

	public:
		// Array of blocks the chunk has.
		unsigned int blocks[CHUNK_VOLUME];
		// The chunk has been modified since last iteration.
		bool modified;

		// List of added vertices. Should be clear unless modified is true.
		std::list<float> added_vertices;
		// List of added uvs. Should be clear unless modified is true.
		std::list<float> added_uvs;
		// List of removed data. Should be clear unless modified is true.
		std::pair<float, unsigned int> removed_data;

		// Initializer.
		int init(unsigned int x, unsigned int y, unsigned int z);

		// Returns the coordinates of the given index.
		static void get_coords(float& x, float& y, float& z, const unsigned int& index);

		// Retuns the specified block's type.
		unsigned int get_front_block(const unsigned int& index) const;
		unsigned int get_back_block(const unsigned int& index) const;

		unsigned int get_up_block(const unsigned int& index) const;
		unsigned int get_down_block(const unsigned int& index) const;

		unsigned int get_left_block(const unsigned int& index) const;
		unsigned int get_right_block(const unsigned int& index) const;
};

#endif