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

void main(void)
{
	vec4 lightColor = vec4(lightColor, 1.0);
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

	vec3 lightVector = lightPos - worldPos.xyz / worldPos.w;

	// Light attenuation
	float lightDistance = length(lightPos - worldPos.xyz / worldPos.w);
	float attenuation = 1.0 / (kc + (kl * lightDistance) + (kq * (lightDistance * lightDistance)));

	float diff = max(dot(normalize(lightVector), normalize(worldNorm)), 0.0);
	vec4 diffuse = diff * lightColor * attenuation;
	vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

	fragColor = vec4(material.ambient, 1.0) * objectColor + diffuse * vec4(material.diffuse, 1.0);
}