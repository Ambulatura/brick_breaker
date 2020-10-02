#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader {
public:
	uint32_t obj_id;
	std::unordered_map<std::string, int> uniform_cache;

public:
	Shader();
	~Shader();

	void bind() const;
	void unbind() const;

	std::string parser(const std::string& file_path) const;
	uint32_t create(const std::string& vertex_shader, const std::string& fragment_shader) const;
	uint32_t compile(const std::string& shader, int type) const;

	const int get_uniform_location(const std::string& name);
	void set_uniform_matrix4f(const std::string& name, glm::mat4& matrix);
	void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);

};

#endif // !SHADER_H
