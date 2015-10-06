// Version du GLSL

#version 150 core


// Entrées

in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normal;


// Uniform

uniform mat4 transformation;
uniform mat4 projection;
uniform mat4 modelview;
uniform vec3 lightPosition;
uniform vec3 lightColor;


// Sortie

out vec2 coordTexture;
out vec3 Normal;
out vec3 lightVector;
out vec3 CameraVector;


// Fonction main

void main()
{
    // Position finale du vertex en 3D
	
	vec4 worldPosition = modelview * vec4(in_Vertex, 1.0);

    gl_Position = projection * worldPosition;


    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;
	
	
	Normal = (modelview *  vec4(in_Normal, 0.0)).xyz;
	lightVector = lightPosition - worldPosition.xyz;
	
	CameraVector = (inverse(modelview) * vec4(0.0,0.0,0.0,1.0)).xyz;
}







