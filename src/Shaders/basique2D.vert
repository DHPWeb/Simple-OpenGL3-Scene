// Vertex Shader
// Version du GLSL 

#version 150 core

// Entrée shader

in vec2 in_vertex;

// Fonction main 

void main()
{
	// Position finale du vertex
	
	gl_Position = vec4(in_vertex, 0.0,1.0);
}