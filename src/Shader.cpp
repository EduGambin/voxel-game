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
		this->error_info = "Shader files not succesfully load";
		return -1;
	}

	const char* vShaderCode = vertex_code.c_str();
	const char* fShaderCode = fragment_code.c_str();

	int success;
	char info_log[1024];

	// Compiling the vertex shader.
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 1024, 0, info_log);
		std::string info_log_string(info_log);
		this->error_info = "Vertex shader compilation failed\n" + info_log_string;
		return -1;
	}

	// Compiling the fragment shader.
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 1024, 0, info_log);
		std::string info_log_string(info_log);
		this->error_info = "Fragment shader compilation failed\n" + info_log_string;
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
		glGetProgramInfoLog(this->id, 1024, 0, info_log);
		std::string info_log_string(info_log);
		this->error_info = "Shader program linking failed\n" + info_log_string;
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

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}	

void Shader::set_mat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}


unsigned int Shader::get_id() const
{
	return this->id;
}

std::string Shader::get_error_info() const
{
	return this->error_info;
}