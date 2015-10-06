#include "WaterShader.h"

// Constructeur 

WaterShader::WaterShader(float longueur, float largeur) : m_shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag")
{
	// chargement du shader

	m_shader.charger();

	// Variables 

	float verticesTmp[] = {
		-longueur, 0, -largeur, longueur, 0, -largeur, longueur, 0, largeur,     // Triangle 1
		-longueur, 0, -largeur, -longueur, 0, largeur, longueur, 0, largeur	     // Triangle 2
	};

	float colorTmp[] = { 
		0.0, 0.0, 1.0,     0.0, 0.0, 1.0,     0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,     0.0, 0.0, 1.0,     0.0, 0.0, 1.0 };


	for (int i = 0; i < 18; i++)
	{
		m_vertices[i] = verticesTmp[i];
		m_color[i] = colorTmp[i];
	}
}

// Destructeur

WaterShader::~WaterShader()
{

}

// Méthode Afficher

void WaterShader::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
	// Utilisation du Shader 

	glUseProgram(m_shader.getProgramID());

	// Envoi des vertices 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);

	// Envoi de la couleur

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_color);
	glEnableVertexAttribArray(1);

	// Envoi des matrices 

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


	// Rendu 

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Désactivation des tableaux

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// Désactivation du Shader

	glUseProgram(0);
}