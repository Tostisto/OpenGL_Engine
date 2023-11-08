#version 460
out vec4 FragColor;

in vec3 TextureCoords;

uniform samplerCube textureUnitID;

void main()
{    
    FragColor = texture(textureUnitID, TextureCoords);
}