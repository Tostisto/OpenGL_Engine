#version 330

in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

void main (void)
{
	vec4 lightColor = vec4(0.785, 0.347, 0.812, 1.0);
	vec3 lightPosition = vec3 (-10.0 ,15.0 ,15.0);

	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);

	vec3 lightVector = lightPosition - worldPos.xyz ;

	float diff = max ( dot ( normalize ( lightVector ) , normalize ( worldNorm )) ,0.0);
	vec4 diffuse = diff * lightColor ;
	vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

	fragColor = (ambient + diffuse) * objectColor ;
}