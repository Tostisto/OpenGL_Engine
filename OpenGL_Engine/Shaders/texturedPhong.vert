#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;

out vec3 worldPos;
out vec3 worldNorm;
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	texCoord = vt;

	vec4 worldPositions = modelMatrix * vec4(vp, 1.0);

	worldPos = worldPositions.xyz / worldPositions.w;
	
	worldNorm = transpose(inverse(mat3(modelMatrix))) * vn;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}