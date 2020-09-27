#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
private:
	unsigned int obj_id;

public:
	VertexBuffer();
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};

#endif // !VERTEX_BUFFER_H
