#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Block.hpp"

#define CHUNK_LENGTH 	16
#define CHUNK_AREA 		256
#define CHUNK_VOLUME 	4096

class Chunk
{
	public:
		unsigned int x, y, z;
		unsigned int blocks[CHUNK_VOLUME];
		bool modified;
		Chunk();

		static void get_coords(float& x, float& y, float& z, unsigned int index);

		const unsigned int get_front_block(unsigned int index) const;
		const unsigned int get_back_block(unsigned int index) const;

		const unsigned int get_up_block(unsigned int index) const;
		const unsigned int get_down_block(unsigned int index) const;

		const unsigned int get_left_block(unsigned int index) const;
		const unsigned int get_right_block(unsigned int index) const;
};

#endif