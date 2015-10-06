#ifndef DEF_WATERSHADER
#define DEF_WATERSHADER

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

class WaterShader
{
public :

	WaterShader(float longueur, float largeur);
	~WaterShader();

	void afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
	Shader m_shader;

	float m_vertices[18];
	float m_color[18];
};



#endif