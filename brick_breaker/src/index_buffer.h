#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstdint>

class IndexBuffer {
private:
	uint32_t obj_id;

public:
	IndexBuffer();
	~IndexBuffer();
	
	void bind() const;
	void unbind() const;

	void buffer_data(uint32_t* indices, uint32_t size, uint32_t usage) const;
};

#endif // !INDEX_BUFFER_H
