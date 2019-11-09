#include "Quad.hpp"

Quad::Quad()
{
	this->valid = false;
	this->drawn = false;
}

void Quad::initialize(glm::vec3 ul, glm::vec3 ur, glm::vec3 dr, glm::vec3 dl,
	unsigned int texture, bool is_drawn)
{
	this->vertices[0] = ul;
	this->vertices[1] = ur;
	this->vertices[2] = dr;
	this->vertices[3] = dl;

	this->texture = texture;
	this->drawn = is_drawn;
	this->valid = true;
}

int Quad::triangles(tri* first, tri* second)
{
	if (first == nullptr || second == nullptr || !this->valid)
		return -1;
	
	first->
}