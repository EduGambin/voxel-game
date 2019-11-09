#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <array>

#define VERT_PER_FACE 18

#define BLOCK_AIR 0
#define BLOCK_GRASS 1

class Block
{
	public:
		static std::array<const float, VERT_PER_FACE> front_face;
		static std::array<const float, VERT_PER_FACE> back_face;
		static std::array<const float, VERT_PER_FACE> up_face;
		static std::array<const float, VERT_PER_FACE> down_face;
		static std::array<const float, VERT_PER_FACE> left_face;
		static std::array<const float, VERT_PER_FACE> right_face;
};

#endif