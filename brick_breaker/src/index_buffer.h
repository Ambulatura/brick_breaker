#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
private:
	unsigned int obj_id;

public:
	IndexBuffer();
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	void buffer_data(unsigned int* indices, size_t size, unsigned int usage) const;
};

#endif // !INDEX_BUFFER_H
