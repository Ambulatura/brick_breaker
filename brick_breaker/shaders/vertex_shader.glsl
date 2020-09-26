# version 330

layout (location = 0) in vec4 position;

uniform mat4 u_ortho; 

void main() {
	gl_Position = u_ortho * position;
}