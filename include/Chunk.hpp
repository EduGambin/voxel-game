#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Block.hpp"

#define CHUNK_LENGTH 	16
#define CHUNK_AREA 		256
#define CHUNK_VOLUME 	4096

class Chunk
{
	private:
		// Position of the chunk in the world.
		unsigned int x, y, z;

	public:
		// Array of blocks the chunk has.
		unsigned int blocks[CHUNK_VOLUME];
		// The chunk has been modified since last iteration.
		bool modified;

		// Constructor.
		Chunk();

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