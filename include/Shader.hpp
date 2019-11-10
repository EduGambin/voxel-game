#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
	private:
		// The program's ID.
		unsigned int id;
		// The program's info.
		std::string info;

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

		// Getters and setters.
		unsigned int get_id() const;
		std::string get_info() const;
};

#endif