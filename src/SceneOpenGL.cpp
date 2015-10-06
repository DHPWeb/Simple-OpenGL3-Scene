#include "SceneOpenGL.h"
#include "Cube.h"
#include "Input.h"
#include "Texture.h"
#include "Camera.h"
#include "Caisse.h"
#include "Skybox.h"
#include "ObjLoader.h"
#include "WaterPlan.h"
#include "WaterShader.h"
#include "mesh.h"
#include "Terrain.h"


// Constructeur de Destructeur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0), m_input()
{

}


SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
	// Initialisation de la SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}


	// Version d'OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	// Création de la fenêtre

	m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}


	// Création du contexte OpenGL

	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

	if (m_contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

	return true;
}


bool SceneOpenGL::initGL()
{
	// On initialise GLEW

	GLenum initialisationGLEW(glewInit());


	// Si l'initialisation a échoué :

	if (initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


		// On quitte la SDL

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

	// Ativation du Depth Buffer

	glEnable(GL_DEPTH_TEST);

	

	// Activation de la lumière

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glShadeModel(GL_SMOOTH);


	// Tout s'est bien passé, on retourne true

	return true;
}


void SceneOpenGL::bouclePrincipale()

{
	glCullFace(GL_BACK);
	std::cout << "Vrai : " << true << std::endl;

	// Variables 

	unsigned int frameRate(1000 / 50);
	Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);
	float angle = 0.0f;
	float px = 15.0f;
	float py = 0.0f;
	float pz = -10.0f;

	// Matrices 
	mat4 projection;
	mat4 modelview;
	vec3 lightPosition = vec3(0.0, 50.0, 20.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	// Camera 

	Camera camera(vec3(25, 24, -25), vec3(3, 3, 3), vec3(0, 1, 0), 0.5, 0.5);

	// Objet

	Cube cube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
	cube.charger();

	Caisse caisse(2.0, "Shaders/texture2.vert", "Shaders/texture2.frag", "Texture/crate03.jpg");
	caisse.charger();


	// Terrain

	Terrain terre(0, 0, "Texture/veg004.jpg");
	terre.charger();
	Terrain terre2(1, 0, "Texture/veg004.jpg");
	terre2.charger();

	// ObjLoader
	Mesh dragon("models/Dragon/dragon.obj");
	Texture dragonTex("models/Dragon/yel.png");
	Shader dragonShad("Shaders/Texture2.vert", "Shaders/Texture2.frag");
	dragonShad.charger();
	dragonTex.charger();

	Mesh stall("models/Stall/stall.obj");
	Texture stallTex("models/Stall/stallTexture.png");
	stallTex.charger();

	Mesh person("models/Person/person.obj");
	Texture personTex("Texture/playerTexture2.png");
	personTex.charger();
	
	WaterPlan sol(20, 20, 1, 1, "Shaders/Texture2.vert", "Shaders/Texture2.frag", "Texture/grassy.png");
	
	

	// Skybox


	Skybox hourglass("Skybox/hourglass/front.jpg",
		"Skybox/hourglass/back2.jpg",
		"Skybox/hourglass/left.jpg",
		"Skybox/hourglass/right2.jpg",
		"Skybox/hourglass/top2.jpg",
		"Shaders/texture.vert", "Shaders/texture.frag");
	 hourglass.charger();


	projection = perspective(70.0, (double)m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
	modelview = mat4(1.0);
	


	// Boucle principale

	while (!m_input.terminer())
	{
		// On définit le temps de début de boucle

		debutBoucle = SDL_GetTicks();

		// Gestion des évènements

		m_input.updateEvenements();

		if (m_input.getTouche(SDL_SCANCODE_ESCAPE))
			break;

		// Gestion du déplacement de la caméra

		camera.deplacer(m_input);
		m_input.capturePointeur(true);
		m_input.afficherPointeur(false);

		

		// Nettoyage de l'ecran
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		

		// Placement de la camera

		camera.lookAt(modelview);

		glm::mat4 sauvegardeModelview = modelview;

		// Rendu

		hourglass.Afficher(projection, modelview);
		sol.afficher(projection,modelview);

		//water.afficher(projection, modelview);



		// Dragon

		glUseProgram(dragonShad.getProgramID());
	
		modelview = rotate(modelview,angle, glm::vec3(0, 1, 0));

		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "shineDamper"), 10.0);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "reflectivity"), 1.0);

		glBindTexture(GL_TEXTURE_2D, dragonTex.getID());
		dragon.Draw();

		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);

		modelview = sauvegardeModelview;

		terre.afficher(projection, modelview, lightPosition, lightColor);
		terre2.afficher(projection, modelview, lightPosition, lightColor);

		modelview = translate(modelview, glm::vec3(-4.0, 0.0, 0.0));
		sauvegardeModelview = modelview;
		modelview = translate(modelview, glm::vec3(10, 0, -10));

		glUseProgram(dragonShad.getProgramID());

		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "shineDamper"), 10.0);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "reflectivity"), 1.0);

		glBindTexture(GL_TEXTURE_2D, stallTex.getID());
		stall.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		modelview = translate(modelview, glm::vec3(px, py, pz));

		glUseProgram(dragonShad.getProgramID());

		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "shineDamper"), 10.0);
		glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "reflectivity"), 1.0);

		glBindTexture(GL_TEXTURE_2D, personTex.getID());
		person.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		if (m_input.getTouche(SDL_SCANCODE_T))
		{
			pz += 0.1f;
			modelview = translate(modelview, glm::vec3(px, py, pz));
			glUseProgram(dragonShad.getProgramID());

			glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
			glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "shineDamper"), 10.0);
			glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "reflectivity"), 1.0);
			glBindTexture(GL_TEXTURE_2D, personTex.getID());
			//person.Draw();
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);

		}
		if (m_input.getTouche(SDL_SCANCODE_G))
		{
			pz -= 0.1f;
			modelview = translate(modelview, glm::vec3(px, py, pz));
			glUseProgram(dragonShad.getProgramID());

			glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(dragonShad.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
			glUniform3f(glGetUniformLocation(dragonShad.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "shineDamper"), 10.0);
			glUniform1f(glGetUniformLocation(dragonShad.getProgramID(), "reflectivity"), 1.0);
			glBindTexture(GL_TEXTURE_2D, personTex.getID());
			//person.Draw();
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);

		}

		modelview = sauvegardeModelview;

	
		cube.afficher(projection, modelview);

		modelview = sauvegardeModelview;

		if (angle == 360)
			angle = 0;
		angle+=0.1;

		// Actualisation de la fenêtre

		SDL_GL_SwapWindow(m_fenetre);

		// Calcul du temps ecoulé

		finBoucle = SDL_GetTicks();
		tempsEcoule = finBoucle - debutBoucle;

		// Si nécessaire, on met en pause le proframme

		if (tempsEcoule < frameRate)
			SDL_Delay(frameRate - tempsEcoule);
	}
}

