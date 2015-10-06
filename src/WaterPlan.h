#ifndef DEF_WATERPLAN
#define DEF_WATERPLAN

// Includes OpenGL

#include <GL\glew.h>

// Include GLM 

#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <GLM\gtx\transform.hpp>

// Includes

#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"

// Classe WaterPlan

class WaterPlan
{
public:
	WaterPlan(float longueur, float largeur, float repetitionLongueur, float repetitionLargeur, std::string vertShader, std::string fragShader, std::string Texture);
	~WaterPlan();

	void afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
	Shader m_shader;
	Texture m_TexWater;

	float m_vertices[18];
	float m_coordText[12];
};




#endif