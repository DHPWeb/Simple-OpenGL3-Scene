// Couleur 2D vertex Shader

// Version du GLSL

#version 150 core 


// Entrée du Shader

in vec2 in_Vertex;
in vec4 in_Color;

// Sortie du Shader

out vec4 color;

// Fonction main

void main()
{
	// Position finale du vertex
	
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
	
	// Envoi de la couleur au Fragment Shader
	
	 color = in_Color;
	 
}
