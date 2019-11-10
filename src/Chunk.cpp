#include "Chunk.hpp"
#include <iostream>

Chunk::Chunk()
{
	for (int i = 0; i < CHUNK_VOLUME; i++) blocks[i] = Block::GRASS_BLOCK;
	modified = true;
	x = y = z = 0;
}

void Chunk::get_coords(float& x, float& y, float& z, const unsigned int& index)
{
	x = (float) (index % CHUNK_LENGTH);
	y = (float) (index / CHUNK_AREA);
	z = -1.0f * (float)((index % CHUNK_AREA) / CHUNK_LENGTH);
}

unsigned int Chunk::get_front_block(const unsigned int& index) const
{
	if (((index % CHUNK_AREA) / CHUNK_LENGTH) == 0) return Block::AIR_BLOCK;
	else return blocks[index - CHUNK_LENGTH];
}

unsigned int Chunk::get_back_block(const unsigned int& index) const
{
	if (- (int)((index % CHUNK_AREA) / CHUNK_LENGTH) == -CHUNK_LENGTH + 1) return Block::AIR_BLOCK;
	else return blocks[index + CHUNK_LENGTH];
}

unsigned int Chunk::get_up_block(const unsigned int& index) const
{
	if (index / CHUNK_AREA == CHUNK_LENGTH - 1) return Block::AIR_BLOCK;
	else return blocks[index + CHUNK_AREA];
}

unsigned int Chunk::get_down_block(const unsigned int& index) const
{
	if (index / CHUNK_AREA == 0) return Block::AIR_BLOCK;
	else return blocks[index - CHUNK_AREA];
}

unsigned int Chunk::get_left_block(const unsigned int& index) const
{
	if (index % CHUNK_LENGTH == 0) return Block::AIR_BLOCK;
	else return blocks[index - 1];
}

unsigned int Chunk::get_right_block(const unsigned int& index) const
{
	if (index % CHUNK_LENGTH == CHUNK_LENGTH - 1) return Block::AIR_BLOCK;
	else return blocks[index + 1];
}