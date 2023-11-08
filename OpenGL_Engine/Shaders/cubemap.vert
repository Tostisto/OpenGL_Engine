#version 460
layout (location = 0) in vec3 vp;

out vec3 TextureCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    TextureCoords = vp;
    gl_Position = projectionMatrix * viewMatrix * vec4(vp, 1.0);
}  