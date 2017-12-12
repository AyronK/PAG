#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexture;

out vec2 fragVertexTexture;
smooth out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragVertexTexture = vertexTexture;
	Normal = vertexNormal;
	FragPos = vec3(model * vec4(vertexPosition, 1.0));
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
}