#include "Chunk.hpp"

Chunk::Chunk()
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		blocks[i] = BLOCK_GRASS;
	}
	modified = true;
}

void Chunk::get_coords(float& x, float& y, float& z, unsigned int index)
{
	x = index % CHUNK_LENGTH;
	y = index / CHUNK_AREA;
	z = - (index % CHUNK_AREA) / CHUNK_LENGTH;
}

const unsigned int Chunk::get_front_block(unsigned int index) const
{
	if (- (index % CHUNK_AREA) / CHUNK_LENGTH == 0) return BLOCK_AIR;
	else return blocks[index - CHUNK_LENGTH];
}

const unsigned int Chunk::get_back_block(unsigned int index) const
{
	if (- (index % CHUNK_AREA) / CHUNK_LENGTH == -CHUNK_LENGTH + 1) return BLOCK_AIR;
	else return blocks[index + CHUNK_LENGTH];
}

const unsigned int Chunk::get_up_block(unsigned int index) const
{
	if (index / CHUNK_AREA == CHUNK_LENGTH - 1) return BLOCK_AIR;
	else return blocks[index + CHUNK_AREA];
}

const unsigned int Chunk::get_down_block(unsigned int index) const
{
	if (index / CHUNK_AREA == 0) return BLOCK_AIR;
	else return blocks[index - CHUNK_AREA];
}

const unsigned int Chunk::get_left_block(unsigned int index) const
{
	if (index % CHUNK_LENGTH == 0) return BLOCK_AIR;
	else return blocks[index - 1];
}

const unsigned int Chunk::get_right_block(unsigned int index) const
{
	if (index % CHUNK_LENGTH == CHUNK_LENGTH - 1) return BLOCK_AIR;
	else return blocks[index + 1];
}
