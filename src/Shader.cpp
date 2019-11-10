#include "Shader.hpp"

int Shader::make_program(const char* vertex_path, const char* fragment_path)
{
	std::string vertex_code, fragment_code;
	std::ifstream v_shader_file, f_shader_file;

	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << v_shader_file.rdbuf();
		fShaderStream << f_shader_file.rdbuf();

		v_shader_file.close();
		f_shader_file.close();

		vertex_code = vShaderStream.str();
		fragment_code = fShaderStream.str();
	}
	catch(std::ifstream::failure &e)
	{
		this->info = "ERROR::SHADER::FILES_NOT_SUCCESFULLY_LOAD";
		return -1;
	}

	const char* vShaderCode = vertex_code.c_str();
	const char* fShaderCode = fragment_code.c_str();

	int success;
	char info_log[512];

	// Compiling the vertex shader.
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, 0, info_log);
		std::string info_log_string(info_log);
		this->info = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + info_log_string;
		return -1;
	}

	// Compiling the fragment shader.
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, 0, info_log);
		std::string info_log_string(info_log);
		this->info = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + info_log_string;
		glDeleteShader(vertex_shader);
		return -1;
	}

	// Creating the shader program.
	this->id = glCreateProgram();
	glAttachShader(this->id, vertex_shader);
	glAttachShader(this->id, fragment_shader);
	glLinkProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->id, 512, 0, info_log);
		std::string info_log_string(info_log);
		this->info = "ERROR::SHADER::POROGRAM::LINKING_FAILED\n" + info_log_string;
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return -1;
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return 0;
}

void Shader::use()
{
	glUseProgram(this->id);
}

void Shader::set_bool(const std::string &name, const bool& value) const
{         
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value); 
}

void Shader::set_int(const std::string &name, const int& value) const
{ 
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value); 
}

void Shader::set_float(const std::string &name, const float& value) const
{ 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
} 

unsigned int Shader::get_id() const
{
	return this->id;
}

std::string Shader::get_info() const
{
	return this->info;
}