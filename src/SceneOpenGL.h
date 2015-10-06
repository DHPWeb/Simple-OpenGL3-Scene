#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL

// Includes OpenGL
#include <gl\glew.h>


// Includes GLM
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <GLM\gtc\type_ptr.hpp>


// Autres Includes
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Input.h"

using namespace glm;

// Classe

class SceneOpenGL
{
public:

	SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
	~SceneOpenGL();

	bool initialiserFenetre();
	bool initGL();
	void bouclePrincipale();


private:

	std::string m_titreFenetre;
	int m_largeurFenetre;
	int m_hauteurFenetre;

	SDL_Window* m_fenetre;
	SDL_GLContext m_contexteOpenGL;
	SDL_Event m_evenements;

	// Objet Input pour la gestion des évènements

	Input m_input;
};

void readOBJ();

#endif 