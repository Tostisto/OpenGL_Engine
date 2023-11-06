#version 330

in vec4 worldPos;
in vec3 worldNorm;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D textureUnitID;

void main(void)
{	
	
	vec4 texColor = texture(textureUnitID, texCoord);

	fragColor = texColor;
}