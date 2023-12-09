#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the texCoord variable has attribute position 1
  
out vec2 TexCoord; // declare a vec2 variable to pass the texture coordinates to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord; // pass the texture coordinates to the fragment shader
} 
