#ifndef DEF_CAMERA
#define DEF_CAMERA

// Includes 
// MATH
#define _USE_MATH_DEFINES
#include <math.h>

// GLM

#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Input.h"

// Classe

class Camera
{
public:

	Camera();
	Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical, float sensibilite, float vitesse);

	// Méthodes 

	void orienter(int xRel, int yRel);
	void deplacer(Input const &input);
	void lookAt(glm::mat4 &modelview);

	// Getters et Setters

	void setPointCible(glm::vec3 pointCible);
	void setPosition(glm::vec3 position);

	float getSensibilite() const;
	float getVitesse() const;

	void setSensibilite(float sensibilite);
	void setVitesse(float vitesse);

	~Camera();

private:

	// Attributs d'orientation

	float m_phi;
	float m_theta;
	glm::vec3 m_orientation;

	// Attributs de deplacement 

	glm::vec3 m_axeVertical;
	glm::vec3 m_deplacementLateral;

	glm::vec3 m_position;
	glm::vec3 m_pointCible;

	float m_sensibilite;
	float m_vitesse;

};

#endif