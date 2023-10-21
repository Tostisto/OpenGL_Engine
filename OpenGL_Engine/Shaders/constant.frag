#version 330

in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

void main (void)
{	
	vec4 ambient = vec4 (0.385 ,0.647 ,0.812 ,1.0);

	fragColor = ambient;
}