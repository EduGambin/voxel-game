#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <list>
#include <utility>

#include "Global.hpp"

// Chunk definitions.
#define CHUNK_LENGTH	  16
#define CHUNK_AREA		 256
#define CHUNK_VOLUME 	4096

#define CHUNK_BROTHERS 6

// Block definitions.
#define BLOCK_FPF_VERTICES 	18
#define BLOCK_FPF_UVS		12

#define BLOCK_AIR 	 0
#define BLOCK_GRASS 1
#define BLOCK_DIRT	 2

#define BLOCK_FRONT_FACE_BIT 	 1	// 000001
#define BLOCK_BACK_FACE_BIT 	 2	// 000010
#define BLOCK_UP_FACE_BIT		 4	// 000100
#define BLOCK_DOWN_FACE_BIT 	 8	// 001000
#define BLOCK_LEFT_FACE_BIT 	16	// 010000
#define BLOCK_RIGHT_FACE_BIT 	32	// 100000

// Texture definitions.
#define TEXTURE_LENGTH 			16.0f
#define TEXTURE_ATLAS_WIDTH 	64.0f
#define TEXTURE_ATLAS_HEIGHT	32.0f

class Chunk
{
	private:
		// Position of the chunk in the world.
		int x, y, z;
		// Array of blocks the chunk has.
		int blocks[CHUNK_VOLUME];
		// Array of brothers in the following order: front, back, up, down, left, right.
		Chunk* brothers[CHUNK_BROTHERS];

		// Adds a single face to the added data in the correct order of coordinates and uv's.
		void add_face_data(const float* face_vertices, const float& world_x, const float& world_y, const float& world_z, const float& s_offset, const float& t_offset);
		// Adds all the drawable faces to the added data.
		void add_faces(const int& face_bits, const int& block_type, const float& x, const float& y, const float& z);
		// Load all the just created data to the added data.
		void load_data();

		// Retuns the face-dictated block's type. The face_bit variable must be only one of the class bits. Also the index won't be checked, so make sure it is correct before using it.
		int get_face_block(const int& face_bit, const int& index) const;

	public:
		// The chunk has been modified since last draw call.
		bool modified;

		// List of added data. Should be clear unless modified is true.
		std::list<float> added_data;
		// Contains the first element and the number of elements that should be removed.
		std::pair<float, int> removed_data;

		Chunk();	// TODO Remove the constructor.

		// Initializer with the chunk coordinates and the brothers in the following order: front, back, up, down, left, right.
		int init(int x, int y, int z, Chunk** brothers);
};

#endif