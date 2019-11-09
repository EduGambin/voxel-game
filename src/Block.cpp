#include "Block.hpp"

std::array<const float, VERT_PER_FACE> Block::front_face =
{
	// First triangle.
	0.0f, 0.0f, 0.0f,	// Left-bottom-front.
	0.5f, 0.0f, 0.0f,	// Right-bottom-front.
	0.5f, 0.5f, 0.0f,	// Right-top_front.

	// Second triangle.
	0.5f, 0.5f, 0.0f,	// Right-top_front.
	0.0f, 0.5f, 0.0f,	// Left-top_front.
	0.0f, 0.0f, 0.0f,	// Left-bottom-front.
};

std::array<const float, VERT_PER_FACE> Block::back_face =
{
	// First triangle.
	0.5f, 0.0f, -0.5f,	// Right-bottom-back.
	0.0f, 0.0f, -0.5f,	// Left-bottom-back.
	0.0f, 0.5f, -0.5f,	// Left-top-back.

	// Second triangle.
	0.0f, 0.5f, -0.5f,	// Left-top-back.
	0.5f, 0.5f, -0.5f,	// Right-top-back.
	0.5f, 0.0f, -0.5f,	// Right-bottom-back.
};

std::array<const float, VERT_PER_FACE> Block::up_face =
{
	// First triangle.
	0.0f, 0.5f,  0.0f,	// Left-top_front.
	0.5f, 0.5f,  0.0f,	// Right-top_front.
	0.5f, 0.5f, -0.5f,	// Right-top-back.

	// Second triangle.
	0.5f, 0.5f, -0.5f,	// Right-top-back.
	0.0f, 0.5f, -0.5f,	// Left-top-back.
	0.0f, 0.5f,  0.0f,	// Left-top_front.
};

std::array<const float, VERT_PER_FACE> Block::down_face =
{
	// First triangle.
	0.0f, 0.0f, -0.5f,	// Left-bottom-back.
	0.5f, 0.0f, -0.5f,	// Right-bottom-back.
	0.5f, 0.0f,  0.0f,	// Right-bottom-front.

	// Second triangle.
	0.5f, 0.0f,  0.0f,	// Right-bottom-front.
	0.0f, 0.0f,  0.0f,	// Left-bottom-front.
	0.0f, 0.0f, -0.5f,	// Left-bottom-back.
};

std::array<const float, VERT_PER_FACE> Block::left_face =
{
	// First triangle.
	0.0f, 0.0f, -0.5f,	// Left-bottom-back.
	0.0f, 0.0f,  0.0f,	// Left-bottom-front.
	0.0f, 0.5f,  0.0f,	// Left-top_front.

	// Second triangle.
	0.0f, 0.5f,  0.0f,	// Left-top_front.
	0.0f, 0.5f, -0.5f,	// Left-top-back.
	0.0f, 0.0f, -0.5f,	// Left-bottom-back.
};

std::array<const float, VERT_PER_FACE> Block::right_face =
{
	// First triangle.
	0.5f, 0.0f,  0.0f,	// Right-bottom-front.
	0.5f, 0.0f, -0.5f,	// Right-bottom-back.
	0.5f, 0.5f, -0.5f,	// Right-top-back.

	// Second triangle.
	0.5f, 0.5f, -0.5f,	// Right-top-back.
	0.5f, 0.5f,  0.0f,	// Right-top_front.
	0.5f, 0.0f,  0.0f,	// Right-bottom-front.
};