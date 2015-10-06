#ifndef DEF_TERRAIN
#define DEF_TERRAIN

// Includes OpenGL

#include <GL\glew.h>

// Includes GLM 

#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <GLM\gtx\transform.hpp>

// Include

#include <string>
#include <vector>
#include <ios>
#include <sstream>
#include <list> // Je sais pas ce que c'est, je sais pas comment ça s'utilise mais je vais les utiliser

// Include local

#include "Shader.h"
#include "Texture.h"

// Macro utile au VBO

#ifndef BUFFER_OFFSET

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif


// Classe Terrain

class Terrain
{
public:
	Terrain(int gridX, int gridZ, std::string textureFileName);
	~Terrain();
	void generateTerrain();
	void charger();
	void afficher(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &lightPosition, glm::vec3 &lightColor);
	void freeMemory();
	
	// getters
	float getX();
	float getZ();
	Texture getTexture();
	GLuint getVaoID();
	

private:

	int const SIZE = 800;
	int const VERTEX_COUNT = 128;


	float *m_normals;
	float *m_vertices;
	float *m_textCoords;
	int *m_indices;

	

	float m_x;
	float m_z;

	int m_tailleVertices;
	int m_tailleNormals;
	int m_tailleIndices;
	int m_tailleTextureCoord;

	Texture m_texture;
	Shader m_shader;

	GLuint m_vboID;
	GLuint m_vaoID;

};


// Classe de rendu de tous les putains de terrains ! FUCK YEAH !!!!!

class TerrainRender
{
public:
	// Constructeur 
	TerrainRender();
	// Destructeur 
	~TerrainRender();

	void Render(std::list<Terrain> terrains);

	void charger(Terrain terrain);
	void uncharge();

private:

	Shader m_shader;

};

#endif
