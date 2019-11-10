#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <array>

namespace Block 
{
	const unsigned int VERTICES_PER_FACE = 18;

	const unsigned int AIR_BLOCK 		= 0;
	const unsigned int GRASS_BLOCK 		= 1;

	static std::array<const float, VERTICES_PER_FACE> front_face =
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

	static std::array<const float, VERTICES_PER_FACE> back_face =
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

	static std::array<const float, VERTICES_PER_FACE> up_face =
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

	static std::array<const float, VERTICES_PER_FACE> down_face =
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

	static std::array<const float, VERTICES_PER_FACE> left_face =
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

	static std::array<const float, VERTICES_PER_FACE> right_face =
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


#endif