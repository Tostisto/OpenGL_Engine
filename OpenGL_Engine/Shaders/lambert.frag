#version 330

in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
};

uniform Material material;

float kc = 1.0;  // Constant attenuation
float kl = 0.1;  // Linear attenuation
float kq = 0.01; // Quadratic attenuation


float LightAttenuation(float distance)
{
	return 1.0 / (kc + (kl * distance) + (kq * (distance * distance)));
}

void main(void)
{
	vec4 lightColor = vec4(lightColor, 1.0);

	vec4 ambient = lightColor * vec4(material.ambient, 1.0);

	vec3 lightVector = lightPos - worldPos.xyz / worldPos.w;

	float attenuation = LightAttenuation(length(lightPos - worldPos.xyz / worldPos.w));

	float diff = max(dot(normalize(lightVector), normalize(worldNorm)), 0.0);
	vec4 diffuse = lightColor * attenuation * vec4(material.diffuse, 1.0) * diff;

	fragColor = ambient + diffuse;
}