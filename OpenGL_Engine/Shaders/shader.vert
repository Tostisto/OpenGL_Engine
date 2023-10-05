#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vc;

uniform mat4 modelMatrix;

out vec4 color;

void main () {
	color = vec4(vc, 1.0);

	gl_Position = modelMatrix * vec4(vp, 1.0);
}