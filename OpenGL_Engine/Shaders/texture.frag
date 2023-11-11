#version 330

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D textureUnitID;

void main(void)
{	
	fragColor = texture(textureUnitID, texCoord);
}