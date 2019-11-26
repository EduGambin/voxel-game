#include "engine/Chunk.hpp"

void get_coords(float& x, float& y, float& z, const int& index)
{
	x = (float) (index % CHUNK_LENGTH);
	y = (float) (index / CHUNK_AREA);
	z = -1.0f * (float)((index % CHUNK_AREA) / CHUNK_LENGTH);
}

const float front_face_vertices[] =
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

const float back_face_vertices[] =
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

const float up_face_vertices[] =
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

const float down_face_vertices[] =
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

const float left_face_vertices[] =
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

const float right_face_vertices[] =
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

const float face_uvs[] =
{
	// First triangle.
									0.0f,									0.0f,	// Left-down.
	TEXTURE_LENGTH / TEXTURE_ATLAS_WIDTH, 									0.0f,	// Right-down.
	TEXTURE_LENGTH / TEXTURE_ATLAS_WIDTH,  TEXTURE_LENGTH / TEXTURE_ATLAS_HEIGHT,	// Right-up.

	// Second triangle.
	TEXTURE_LENGTH / TEXTURE_ATLAS_WIDTH,  TEXTURE_LENGTH / TEXTURE_ATLAS_HEIGHT,	// Right-up.
									0.0f,  TEXTURE_LENGTH / TEXTURE_ATLAS_HEIGHT,	// Left-up.
									0.0f,									0.0f,	// Left-down.
};

const float normals[] =
{
	// Front face.
	 0.0f,  0.0f,  1.0f,

	// Back face.
	 0.0f,  0.0f, -1.0f,

	// Up face.
	 0.0f,  1.0f,  0.0f,

	// Down face.
	 0.0f, -1.0f,  0.0f,

	// Left face.
	-1.0f,  0.0f,  0.0f,

	// Right face.
	 1.0f,  0.0f,  0.0f
};

void Chunk::add_face_data(const float* face_vertices, const float& world_x, const float& world_y, const float& world_z, const float& s_offset, const float& t_offset, const int& face)
{
	int i, j;
	i = j = 0;

	while(i < BLOCK_FPF_VERTICES)
	{
		this->added_data.emplace_back(face_vertices[i++] + world_x);
		this->added_data.emplace_back(face_vertices[i++] + world_y);
		this->added_data.emplace_back(face_vertices[i++] + world_z);
		this->added_data.emplace_back(face_uvs[j++] + s_offset);
		this->added_data.emplace_back(face_uvs[j++] + t_offset);
		this->added_data.emplace_back(normals[face]);
		this->added_data.emplace_back(normals[face + 1]);
		this->added_data.emplace_back(normals[face + 2]);
	}
}

void Chunk::add_faces(const int& face_bits, const int& block_type, const float& x, const float& y, const float& z)
{
	float world_x = (float)(this->x * CHUNK_LENGTH) + x;
	float world_y = (float)(this->y * CHUNK_LENGTH) + y;
	float world_z = (float)(this->z * CHUNK_LENGTH) + z;

	float norm_width = TEXTURE_LENGTH / TEXTURE_ATLAS_WIDTH;
	float norm_height = TEXTURE_LENGTH / TEXTURE_ATLAS_HEIGHT;

	int up_texture, block_texture, down_texture;
	switch (block_type)
	{
		case BLOCK_GRASS:
			up_texture = 0;
			block_texture = 1;
			down_texture = 2;
			break;
		case BLOCK_DIRT:
			up_texture = block_texture = down_texture = 2;
			break;
		default:
			up_texture = block_texture = down_texture = 0;
			break;
	}

	if (face_bits & BLOCK_FRONT_FACE_BIT) this->add_face_data(front_face_vertices, world_x, world_y, world_z, (float)((block_texture % 4) * norm_width), (float)(block_texture / 4) * norm_height, 0);
	if (face_bits & BLOCK_BACK_FACE_BIT) this->add_face_data(back_face_vertices, world_x, world_y, world_z, (float)((block_texture % 4) * norm_width), (float)(block_texture / 4) * norm_height, 3);

	if (face_bits & BLOCK_UP_FACE_BIT) this->add_face_data(up_face_vertices, world_x, world_y, world_z, (float)((up_texture % 4) * norm_width), (float)(up_texture / 4) * norm_height, 6);
	if (face_bits & BLOCK_DOWN_FACE_BIT) this->add_face_data(down_face_vertices, world_x, world_y, world_z, (float)((down_texture % 4) * norm_width), (float)(down_texture / 4) * norm_height, 9);

	if (face_bits & BLOCK_LEFT_FACE_BIT) this->add_face_data(left_face_vertices, world_x, world_y, world_z, (float)((block_texture % 4) * norm_width), (float)(block_texture / 4) * norm_height, 12);
	if (face_bits & BLOCK_RIGHT_FACE_BIT) this->add_face_data(right_face_vertices, world_x, world_y, world_z, (float)((block_texture % 4) * norm_width), (float)(block_texture / 4) * norm_height, 15);
}
void Chunk::load_data()
{
	// The first and last floor will be virtual so there's no need to iterate over them.
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		// If it's an air block, there's nothing to draw.
		if (this->blocks[i] == BLOCK_AIR) continue;

		float x, y, z;
		get_coords(x, y, z, i);
		int face_bits = 0;
		if (this->get_face_block(BLOCK_FRONT_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_FRONT_FACE_BIT;
		if (this->get_face_block(BLOCK_BACK_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_BACK_FACE_BIT;

		if (this->get_face_block(BLOCK_UP_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_UP_FACE_BIT;
		if (this->get_face_block(BLOCK_DOWN_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_DOWN_FACE_BIT;

		if (this->get_face_block(BLOCK_LEFT_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_LEFT_FACE_BIT;
		if (this->get_face_block(BLOCK_RIGHT_FACE_BIT, i) == BLOCK_AIR) face_bits |= BLOCK_RIGHT_FACE_BIT;

		this->add_faces(face_bits, this->blocks[i], x, y, z);
	}
}

Chunk::Chunk()
{
	for (int i = 0; i < CHUNK_VOLUME; i++) this->blocks[i] = BLOCK_GRASS;
}

int Chunk::init(int x, int y, int z, Chunk** brothers)
{
	this->x = x;
	this->y = y;
	this->z = z;

	for (int i = 0; i < CHUNK_BROTHERS; i++) this->brothers[i] = brothers[i];

	this->modified = true;
	this->removed_data = {0.0f, 0};
	this->load_data();

	return APP_SUCCESS;
}

int Chunk::get_face_block(const int& face_bit, const int& index) const
{
	if (face_bit & BLOCK_FRONT_FACE_BIT)
	{
		if ((index % CHUNK_AREA) / CHUNK_LENGTH == 0)
		{
			if (!this->brothers[0]) return BLOCK_AIR;
			else return this->brothers[0]->blocks[index + CHUNK_LENGTH * (CHUNK_LENGTH - 1)];
		}
		else return blocks[index - CHUNK_LENGTH];
	}
	if (face_bit & BLOCK_BACK_FACE_BIT)
	{
		if ((index % CHUNK_AREA) / CHUNK_LENGTH == CHUNK_LENGTH - 1)
		{
			if (!this->brothers[1]) return BLOCK_AIR;
			else return this->brothers[1]->blocks[index - CHUNK_LENGTH * (CHUNK_LENGTH - 1)];
		}
		else return blocks[index + CHUNK_LENGTH];
	}

	if (face_bit & BLOCK_UP_FACE_BIT)
	{
		if (index / CHUNK_AREA == CHUNK_LENGTH - 1)
		{
			if (!this->brothers[2]) return BLOCK_AIR;
			else return this->brothers[2]->blocks[index - CHUNK_AREA * (CHUNK_LENGTH - 1)];
		}
		else return blocks[index + CHUNK_AREA];
	}
	if (face_bit & BLOCK_DOWN_FACE_BIT)
	{
		if (index / CHUNK_AREA == 0)
		{
			if (!this->brothers[3]) return BLOCK_AIR;
			else return this->brothers[3]->blocks[index + CHUNK_AREA * (CHUNK_LENGTH - 1)];
		}
		else return blocks[index - CHUNK_AREA];
	}

	if (face_bit & BLOCK_LEFT_FACE_BIT)
	{
		if (index % CHUNK_LENGTH == 0)
		{
			if (!this->brothers[4]) return BLOCK_AIR;
			else return this->brothers[4]->blocks[index + (CHUNK_LENGTH - 1)];
		}
		else return blocks[index - 1];
	}
	if (face_bit & BLOCK_RIGHT_FACE_BIT)
	{
		if (index % CHUNK_LENGTH == CHUNK_LENGTH - 1)
		{
			if (!this->brothers[5]) return BLOCK_AIR;
			else return this->brothers[5]->blocks[index - (CHUNK_LENGTH - 1)];
		}
		else return blocks[index + 1];
	}

	return BLOCK_AIR;
}