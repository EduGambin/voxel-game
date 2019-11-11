#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
	private:
		// The program's ID.
		unsigned int id;
		// The program's info.
		std::string error_info;

	public:
	
		// Makes a program shader out of a vertex and a fragment shader.
		// Returns 0 on success and -1 otherwise.
		int make_program(const char* vertex_path, const char* fragment_path);
		// Use or activate the shader.
		void use();

		// Uniform functions.
		void set_bool(const std::string &name, const bool& value) const;
		void set_int(const std::string &name, const int& value) const;
		void set_float(const std::string &name, const float& value) const;

		void set_vec2(const std::string& name, const glm::vec2& value) const;
		void set_vec3(const std::string& name, const glm::vec3& value) const;
		void set_vec4(const std::string& name, const glm::vec4& value) const;

		void set_mat2(const std::string& name, const glm::mat2& value) const;
		void set_mat3(const std::string& name, const glm::mat3& value) const;
		void set_mat4(const std::string& name, const glm::mat4& value) const;

		// Getters and setters.
		unsigned int get_id() const;
		std::string get_error_info() const;
};

#endif