#include "SceneOpenGL.h"


int wmain(int argc, char** argv)
{
	// Création de la scène

	SceneOpenGL scene("Test", 800, 800);

	// Initialisation de la scène 

	if (scene.initialiserFenetre() == false)
		return -1;

	if (scene.initGL() == false)
		return -1;

	// Boucle Principale

	scene.bouclePrincipale();

	// Fin du programme 

	return 0;
}