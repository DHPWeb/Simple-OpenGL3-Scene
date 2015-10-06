#include "WaterPlan.h"

// Constructeur 

WaterPlan::WaterPlan(float longueur, float largeur, float repetitionLongueur, float repetitionLargeur, std::string vertShader, std::string fragShader, std::string Texture) :
m_shader(vertShader, fragShader), m_TexWater(Texture)
{	
	// Chargment du Shader

	m_shader.charger();

	// Chargement de la texture

	m_TexWater.charger();

	// Division de la taille

	longueur /= 2.0f;
	largeur /= 2.0f;

	// Vertices Temporaires

	float verticesTmp[] = {
		-longueur, 0, -largeur,         longueur, 0, -largeur,       longueur, 0, largeur,     // Triangle 1
		-longueur, 0, -largeur,        -longueur, 0, largeur,        longueur, 0, largeur	   // Triangle 2
	};   

	// Coordonnées Temporaires

	float coordTmp[] = {
		0, 0,        repetitionLongueur, 0,          repetitionLongueur, repetitionLargeur,      // Triangle 1
		0, 0,        0, repetitionLargeur,           repetitionLongueur, repetitionLargeur       // Triangle 2
	};  


	// Copie des Vertices

	for (int i = 0; i < 18; i++)
		m_vertices[i] = verticesTmp[i];
	
	// Copie des coordonnées

	for (int i = 0; i < 12; i++)
		m_coordText[i] = coordTmp[i];

}


// Destructeur 

WaterPlan::~WaterPlan()
{

}

void WaterPlan::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
	// Utilisation du Shader 

	glUseProgram(m_shader.getProgramID());

	// Envoi des vertices 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);

	// Envoi des coordonnées de texture

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordText);
	glEnableVertexAttribArray(2);

	// Envoi des matrices 

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightPosition"), 0.0, 50.0, 20.0);
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightColor"), 1.0, 1.0, 1.0);
	glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "shineDamper"), 10.0);
	glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "reflectivity"), 1.0);

	// Verrouillage de la texture 

	glBindTexture(GL_TEXTURE_2D, m_TexWater.getID());

	// Rendu 

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Déverrouillage de la texture 

	glBindTexture(GL_TEXTURE_2D, 0);

	// Désactivation des tableaux

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);

	// Désactivation du Shader

	glUseProgram(0);


}