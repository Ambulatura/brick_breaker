#include "shader.h"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

Shader::Shader() {
	obj_id = glCreateProgram();
}

Shader::~Shader() {
	glDeleteProgram(obj_id);
}

void Shader::bind() const {
	glUseProgram(obj_id);
}

void Shader::unbind() const {
	glUseProgram(0);
}

std::string Shader::parser(const std::string& file_path) const {
	std::fstream stream(file_path);
	std::string shader;
	std::string line;
	while (std::getline(stream, line))
		shader += line + '\n';
	return shader;
}

uint32_t Shader::create(const std::string& vertex_shader, const std::string& fragment_shader) const {
	uint32_t vs = compile(vertex_shader, GL_VERTEX_SHADER);
	uint32_t fs = compile(fragment_shader, GL_FRAGMENT_SHADER);
	glAttachShader(obj_id, vs);
	glAttachShader(obj_id, fs);
	glLinkProgram(obj_id);
	glValidateProgram(obj_id);

	int check;

	glGetProgramiv(obj_id, GL_LINK_STATUS, &check);
	if (check == GL_FALSE) {
		int log_length = 0;
		char log[1024];
		glGetProgramInfoLog(obj_id, 1024, &log_length, log);
		std::cout << "[Shader Link Error] " << log << std::endl;

		glDeleteShader(vs);
		glDeleteShader(fs);
		return -1;
	}

	glGetProgramiv(obj_id, GL_VALIDATE_STATUS, &check);
	if (check == GL_FALSE) {
		int log_length = 0;
		char log[1024];
		glGetProgramInfoLog(obj_id, 1024, &log_length, log);
		std::cout << "[Shader Validation Error] " << log << std::endl;

		glDeleteShader(vs);
		glDeleteShader(fs);

		return -1;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return obj_id;
}

uint32_t Shader::compile(const std::string& shader, int type) const {
	uint32_t shader_id = glCreateShader(type);
	const char* shader_source = shader.c_str();
	glShaderSource(shader_id, 1, &shader_source, 0);
	glCompileShader(shader_id);

	int compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int log_length = 0;
		char log[1024];
		glGetShaderInfoLog(shader_id, 1024, &log_length, log);
		std::cout << "[" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Error] " << log << std::endl;

		glDeleteShader(shader_id);
		return -1;
	}

	return shader_id;
}

const int Shader::get_uniform_location(const std::string& name) {
	if (uniform_cache.find(name) != uniform_cache.end())
		return uniform_cache[name];

	int location = glGetUniformLocation(obj_id, name.c_str());;
	if (location == -1)
		std::cout << "'" << name << "' uniform doesn't exist!" << std::endl;

	uniform_cache[name] = location;
	return location;
}

void Shader::set_uniform_matrix4f(const std::string& name, glm::mat4& matrix) {
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}
