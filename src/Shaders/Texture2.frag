// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;
in vec3 Normal;
in vec3 lightVector;
in vec3 CameraVector;


// Uniform

uniform sampler2D texture;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel
	
	vec3 unitNormal = normalize(Normal);
	vec3 unitlLightVector = normalize(lightVector);
	
	float nDot1 = dot(unitNormal, unitlLightVector);
	float brightness = max(nDot1, 0.0);
	vec3 diffuse = brightness * lightColor;
	
	vec3 unitVectorToCamera = normalize(CameraVector);
	vec3 lightDirection = unitlLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection,unitNormal);
	
	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor,shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

    out_Color = vec4(diffuse,1.0) * texture(texture, coordTexture) + vec4(finalSpecular,1.0);
}