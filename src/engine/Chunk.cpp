#include "engine/Chunk.hpp"

void Chunk::add_vertices(int face_bits, float x, float y, float z)
{
	float chunk_x = (float)(this->x * CHUNK_LENGTH);
	float chunk_y = (float)(this->y * CHUNK_LENGTH);
	float chunk_z = (float)(this->z * CHUNK_LENGTH);

	if (face_bits & BLOCK_FRONT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> front_face = Block::front_face;
			this->added_vertices.push_back(front_face[k] + x + chunk_x);
			this->added_vertices.push_back(front_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(front_face[k+2] + z + chunk_z);
		}
	}

	if (face_bits & BLOCK_BACK_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> back_face = Block::back_face;
			this->added_vertices.push_back(back_face[k] + x + chunk_x);
			this->added_vertices.push_back(back_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(back_face[k+2] + z + chunk_z);
		}
	}

	if (face_bits & BLOCK_UP_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> up_face = Block::up_face;
			this->added_vertices.push_back(up_face[k] + x + chunk_x);
			this->added_vertices.push_back(up_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(up_face[k+2] + z + chunk_z);
		}
	}

	if (face_bits & BLOCK_DOWN_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> down_face = Block::down_face;
			this->added_vertices.push_back(down_face[k] + x + chunk_x);
			this->added_vertices.push_back(down_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(down_face[k+2] + z + chunk_z);
		}
	}

	if (face_bits & BLOCK_LEFT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> left_face = Block::left_face;
			this->added_vertices.push_back(left_face[k] + x);
			this->added_vertices.push_back(left_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(left_face[k+2] + z + chunk_z);
		}
	}

	if (face_bits & BLOCK_RIGHT_FACE_BIT)
	{
		for(unsigned int k = 0; k < BLOCK_VPF; k += 3)
		{
			std::array<const float, BLOCK_VPF> right_face = Block::right_face;
			this->added_vertices.push_back(right_face[k] + x);
			this->added_vertices.push_back(right_face[k+1] + y + chunk_y);
			this->added_vertices.push_back(right_face[k+2] + z + chunk_z);
		}
	}
}

void Chunk::add_uvs(int face_bits, unsigned int block_type)
{
	float norm_width, norm_height;
	norm_width = TEXTURE_LENGTH / TEXTURE_ATLAS_WIDTH;
	norm_height = TEXTURE_LENGTH / TEXTURE_ATLAS_HEIGHT;

	unsigned int up_texture, block_texture, down_texture;
	switch (block_type)
	{
		case BLOCK_GRASS:
			up_texture = 0.0f;
			block_texture = 1.0f;
			down_texture = 2.0f;
			break;
		case BLOCK_DIRT:
			up_texture = block_texture = down_texture = 2.0f;
			break;
		default:
			up_texture = block_texture = down_texture = 0.0f;
			break;
	}

	if (face_bits & BLOCK_FRONT_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));
	}

	if (face_bits & BLOCK_BACK_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));
	}

	if (face_bits & BLOCK_UP_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(up_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(up_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(up_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(up_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(up_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((up_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(up_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((up_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(up_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((up_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(up_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(up_texture / 4));
	}

	if (face_bits & BLOCK_DOWN_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(down_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(down_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(down_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(down_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(down_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((down_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(down_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((down_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(down_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((down_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(down_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(down_texture / 4));
	}

	if (face_bits & BLOCK_LEFT_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));
	}

	if (face_bits & BLOCK_RIGHT_FACE_BIT)
	{
		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Down-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-right
		this->added_uvs.push_back(norm_width * (float)(block_texture + 1 % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Up-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)((block_texture / 4) + 1));

		// Down-left
		this->added_uvs.push_back(norm_width * (float)(block_texture % 4));
		this->added_uvs.push_back(norm_height * (float)(block_texture / 4));
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
		this->get_coords(x, y, z, i);
		if (this->get_front_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_FRONT_FACE_BIT;
		if (this->get_back_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_BACK_FACE_BIT;
		if (this->get_up_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_UP_FACE_BIT;
		if (this->get_down_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_DOWN_FACE_BIT;
		if (this->get_left_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_LEFT_FACE_BIT;
		if (this->get_right_block(i) == BLOCK_AIR) face_bits = face_bits | BLOCK_RIGHT_FACE_BIT;

		this->add_vertices(face_bits, x, y, z);
		this->add_uvs(face_bits, this->blocks[i]);
	}
}

int Chunk::init(unsigned int x, unsigned int y, unsigned int z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		if (i / CHUNK_AREA == CHUNK_LENGTH - 1) this->blocks[i] = BLOCK_GRASS;
		else this->blocks[i] = BLOCK_DIRT;
	}

	this->modified = true;
	this->removed_data = {0.0f, 0u};
	this->load_data();

	return APP_SUCCESS;
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