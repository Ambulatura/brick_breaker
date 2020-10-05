#include "object.h"

Object::~Object() {}

const float* Object::get_vertex_positions() const {
	return vertex_positions;
}

const uint32_t* Object::get_vertex_indices() const {
	return vertex_indices;
}

uint32_t Object::get_vertex_size() const {
	return vertex_size;
}

uint32_t Object::get_index_size() const {
	return index_size;
}

/*uint32_t Object::get_vertex_count() const {
	return vertex_count;
}*/

uint32_t Object::get_index_count() const {
	return index_count;
}

uint32_t Object::get_primitive() const
{
	return primitive;
}

uint32_t Object::get_draw_type() const
{
	return draw_type;
}

