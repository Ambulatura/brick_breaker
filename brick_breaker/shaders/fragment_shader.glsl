# version 330

out vec4 color;

in vec4 v_color;

uniform vec4 u_color;


void main() {
    if (v_color.w != 1.0) {
		color = v_color;
	} else {
		color = u_color;
	}
}