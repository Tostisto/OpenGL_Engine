#version 460

#define MAX_LIGHTS 10

in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 cameraPos;

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 color;
	vec3 position;
	vec3 direction;
    int type;
	float cutOff;
	bool enabled;
	Attenuation attenuation;
};

uniform Light light;
uniform Light lights[MAX_LIGHTS];

uniform Light camera_spot_light;

uniform Material material;

float LightAttenuation(float distance, float kc, float kl, float kq)
{
	return 1.0 / (kc + (kl * distance) + (kq * (distance * distance)));
}

vec4 AddDirectionLight(Light light, vec3 worldNorm, vec3 worldPos)
{
	vec4 lightColor = vec4(light.color, 1.0);
	vec4 ambient = lightColor * vec4(material.ambient, 1.0);
	
	vec3 viewVector = cameraPos - worldPos.xyz;
	vec3 reflectionDir = reflect(-light.direction, worldNorm);

	float diff = max(dot(normalize(light.direction), normalize(worldNorm)), 0.0);
	vec4 diffuse = lightColor  * vec4(material.diffuse, 1.0) * diff;

	float spec = pow(max(dot(normalize(reflectionDir), normalize(viewVector)),0.0), material.shininess);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	if (dot(normalize(light.direction), normalize(worldNorm)) > 0.0)
	{
		specular = lightColor * vec4(material.specular, 1.0) * spec;
	}
	
	return ambient + diffuse + specular;
}


vec4 AddPointLight(Light light, vec3 worldNorm, vec3 worldPos)
{
	vec4 lightColor = vec4(light.color, 1.0);
	vec4 ambient = lightColor * vec4(material.ambient, 1.0);
	
	vec3 lightVector = light.position - worldPos.xyz;
	vec3 viewVector = cameraPos - worldPos.xyz;

	float attenuation = LightAttenuation(length(light.position - worldPos), light.attenuation.constant, light.attenuation.linear, light.attenuation.quadratic);

	vec3 reflectionDir = reflect(-lightVector, worldNorm);

	float diff = max(dot(normalize(lightVector), normalize(worldNorm)), 0.0);
	vec4 diffuse = lightColor * attenuation * vec4(material.diffuse, 1.0) * diff;

	float spec = pow(max(dot(normalize(reflectionDir), normalize(viewVector)),0.0), material.shininess);

	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	if (dot(normalize(lightVector), normalize(worldNorm)) > 0.0)
	{
		specular = lightColor * attenuation * vec4(material.specular, 1.0) * spec;
	}

	return ambient + diffuse + specular;
}


vec4 AddSpotLight(Light light, vec3 worldNorm, vec3 worldPos)
{
	vec4 lightColor = vec4(light.color, 1.0);
	vec4 ambient = lightColor * vec4(material.ambient, 1.0);

	vec3 lightVector = light.position - worldPos;
	vec3 viewVector = cameraPos - worldPos;

	float attenuation = LightAttenuation(length(lightVector), light.attenuation.constant, light.attenuation.linear, light.attenuation.quadratic);
	vec3 reflectionDir = reflect(-lightVector, worldNorm);

    float cosTheta = dot(normalize(lightVector), normalize(-light.direction));

    if (cosTheta > light.cutOff)
    {
		float intensity = 1.f/ (1.f - light.cutOff) * (cosTheta - light.cutOff);

		float diff = max(dot(normalize(lightVector), normalize(worldNorm)), 0.0);
		vec4 diffuse = lightColor * attenuation * vec4(material.diffuse, 1.0) * diff * intensity;

		float spec = pow(max(dot(normalize(reflectionDir), normalize(viewVector)),0.0), material.shininess);
        vec4 specular = lightColor * attenuation * vec4(material.specular, 1.0) * spec * intensity;

        return ambient + diffuse + specular;
    }

    return ambient;
}


void main(void)
{
	vec4 result = vec4(0.0);

	if (camera_spot_light.enabled == true)
	{
		result += AddSpotLight(camera_spot_light, worldNorm, worldPos);
	}

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (lights[i].type == 1)
		{
			result += AddPointLight(lights[i], worldNorm, worldPos);
		}
		else if (lights[i].type == 2)
		{
			result += AddDirectionLight(lights[i], worldNorm, worldPos);
		}
		else if (lights[i].type == 3)
		{
			result += AddSpotLight(lights[i], worldNorm, worldPos);
		}
	}

	fragColor = result;
}