#version 330

in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 cameraPos;

void main (void)
{
	vec4 lightColor = vec4(0.785, 0.347, 0.812, 1.0);
	vec3 lightPosition = vec3 (0.0, 15.0, 0.0);
	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);
	
	vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

	vec3 lightVector = lightPosition - worldPos.xyz ;
	vec3 viewVector = cameraPos - worldPos.xyz ;


	vec3 halfwayDir = normalize(lightVector + viewVector);


	vec3 reflectionDir = reflect ( -lightVector , worldNorm );

	float diff = max ( dot ( normalize ( lightVector ) , normalize ( worldNorm )) ,0.0);
	vec4 diffuse = diff * lightColor ;

	float spec = pow ( max ( dot ( normalize ( reflectionDir ) , normalize ( viewVector )) ,0.0) , 32.0);
	vec4 specular = spec * lightColor ;

	fragColor = (ambient + diffuse + specular) * objectColor ;
}