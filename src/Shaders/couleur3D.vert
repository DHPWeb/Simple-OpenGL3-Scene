// Couleur 3D Vertex
// Version du GLSL

#version 150 core

// Entrée 

in vec3 in_Vertex;
in vec3 in_Color;

// Uniform

uniform mat4 projection;
uniform mat4 modelview;

// Sortie

out vec3 color;

// Fonction main 

void main()
{
	// Position finale du vertex
	
	gl_Position = projection * modelview *  vec4(in_Vertex,1.0);
	
	// Envoi de la couleur au fragment Shader
	
	color = in_Color;
}