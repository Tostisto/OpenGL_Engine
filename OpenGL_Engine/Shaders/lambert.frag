#version 330

in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main(void)
{
	vec4 lightColor = vec4(lightColor, 1.0);
	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);

	vec3 lightVector = lightPos - worldPos.xyz ;

	float diff = max(dot(normalize(lightVector), normalize(worldNorm)), 0.0);
	vec4 diffuse = diff * lightColor ;
	vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

	fragColor = (ambient + diffuse) * objectColor ;
}