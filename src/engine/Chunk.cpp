#include "engine/Chunk.hpp"
#include <iostream>

void Chunk::add_vertices(int face_bits, float x, float y, float z)
{
	if (face_bits & FRONT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> front_face = Block::front_face;
			added_vertices.push_back(front_face[k] + x);
			added_vertices.push_back(front_face[k+1] + y);
			added_vertices.push_back(front_face[k+2] + z);
		}
	}

	if (face_bits & BACK_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> back_face = Block::back_face;
			added_vertices.push_back(back_face[k] + x);
			added_vertices.push_back(back_face[k+1] + y);
			added_vertices.push_back(back_face[k+2] + z);
		}
	}

	if (face_bits & UP_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> up_face = Block::up_face;
			added_vertices.push_back(up_face[k] + x);
			added_vertices.push_back(up_face[k+1] + y);
			added_vertices.push_back(up_face[k+2] + z);
		}
	}

	if (face_bits & DOWN_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> down_face = Block::down_face;
			added_vertices.push_back(down_face[k] + x);
			added_vertices.push_back(down_face[k+1] + y);
			added_vertices.push_back(down_face[k+2] + z);
		}
	}

	if (face_bits & LEFT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> left_face = Block::left_face;
			added_vertices.push_back(left_face[k] + x);
			added_vertices.push_back(left_face[k+1] + y);
			added_vertices.push_back(left_face[k+2] + z);
		}
	}

	if (face_bits & RIGHT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> right_face = Block::right_face;
			added_vertices.push_back(right_face[k] + x);
			added_vertices.push_back(right_face[k+1] + y);
			added_vertices.push_back(right_face[k+2] + z);
		}
	}
}

void Chunk::load_data()
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		// If it's an air block, there's nothing to draw.
		if (this->blocks[i] == BLOCK_AIR) continue;

		float x, y, z;
		int face_bits = 0;
		get_coords(x, y, z, i);
		if (get_front_block(i) == BLOCK_AIR) face_bits = face_bits | FRONT_FACE_BIT;
		if (get_back_block(i) == BLOCK_AIR) face_bits = face_bits | BACK_FACE_BIT;
		if (get_up_block(i) == BLOCK_AIR) face_bits = face_bits | UP_FACE_BIT;
		if (get_down_block(i) == BLOCK_AIR) face_bits = face_bits | DOWN_FACE_BIT;
		if (get_left_block(i) == BLOCK_AIR) face_bits = face_bits | LEFT_FACE_BIT;
		if (get_right_block(i) == BLOCK_AIR) face_bits = face_bits | RIGHT_FACE_BIT;

		add_vertices(face_bits, x, y, z);
		// add_uvs(face_bits, this->blocks[i]); // TODO Implement textures.
	}
}

Chunk::Chunk()
{
	for (int i = 0; i < CHUNK_VOLUME; i++) this->blocks[i] = BLOCK_GRASS;
	modified = true;
	x = y = z = 0;
	removed_data = {0.0f, 0};

	load_data();
}

void Chunk::get_coords(float& x, float& y, float& z, const unsigned int& index)
{
	x = (float) (index % CHUNK_LENGTH);
	y = (float) (index / CHUNK_AREA);
	z = -1.0f * (float)((index % CHUNK_AREA) / CHUNK_LENGTH);
}

unsigned int Chunk::get_front_block(const unsigned int& index) const
{
	if (((index % CHUNK_AREA) / CHUNK_LENGTH) == 0) return BLOCK_AIR;
	else return blocks[index - CHUNK_LENGTH];
}

unsigned int Chunk::get_back_block(const unsigned int& index) const
{
	if (- (int)((index % CHUNK_AREA) / CHUNK_LENGTH) == -CHUNK_LENGTH + 1) return BLOCK_AIR;
	else return blocks[index + CHUNK_LENGTH];
}

unsigned int Chunk::get_up_block(const unsigned int& index) const
{
	if (index / CHUNK_AREA == CHUNK_LENGTH - 1) return BLOCK_AIR;
	else return blocks[index + CHUNK_AREA];
}

unsigned int Chunk::get_down_block(const unsigned int& index) const
{
	if (index / CHUNK_AREA == 0) return BLOCK_AIR;
	else return blocks[index - CHUNK_AREA];
}

unsigned int Chunk::get_left_block(const unsigned int& index) const
{
	if (index % CHUNK_LENGTH == 0) return BLOCK_AIR;
	else return blocks[index - 1];
}

unsigned int Chunk::get_right_block(const unsigned int& index) const
{
	if (index % CHUNK_LENGTH == CHUNK_LENGTH - 1) return BLOCK_AIR;
	else return blocks[index + 1];
}