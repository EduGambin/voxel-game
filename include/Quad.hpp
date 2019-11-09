#ifndef QUAD_HPP
#define QUAD_HPP

#include <glm/vec3.hpp>

typedef struct triangle
{
	glm::vec3 first_vert;
	glm::vec3 first_uv;

	glm::vec3 second_vert;
	glm::vec3 second_uv;

	glm::vec3 third_vert;
	glm::vec3 third_uv;
} tri;

class Quad
{
	private:
		bool valid;				// Is the quad correctly initialized.
		bool drawn;				// Should the quad be rendered.
		glm::vec3 vertices[4];	// Vertices of the quad.
		unsigned int texture;	// Texture of the quad.

	public:
		// Default constructor.
		Quad();

		// Initializes the quad.
		void initialize(glm::vec3 ul, glm::vec3 ur, glm::vec3 dr, glm::vec3 dl,
			unsigned int texture, bool is_drawn);
		
		// Puts two triangles containing it's vertices in the input variables.
		// Returns 0 on success or -1 on failure.
		int triangles(tri* first, tri* second);

		// Getters and setters.

		bool isValid();
		bool isDrawn();
		unsigned int getTexture();

		bool setDrawn(bool drawn);
};

#endif