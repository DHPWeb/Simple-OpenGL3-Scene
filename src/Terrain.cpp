#include "Terrain.h"

// CLASS TERRAIN

// Constructeur 

Terrain::Terrain(int gridX, int gridZ, std::string textureFileName) :
m_x((float)gridX * (float)SIZE),
m_z((float)gridZ *(float)SIZE),
m_texture(textureFileName),
m_shader("Shaders/texture.vert", "Shaders/texture.frag")
{
	// Chargement de la texture

	m_texture.charger();

	// Chargement du Shader 

	m_shader.charger();

	// Génération du Terrain

	generateTerrain();


	// Calcul des tailles des tableaux

	m_tailleVertices = ((VERTEX_COUNT * VERTEX_COUNT) * 3) * sizeof(float);
	m_tailleNormals = ((VERTEX_COUNT * VERTEX_COUNT) * 3) * sizeof(float);
	m_tailleTextureCoord = ((VERTEX_COUNT * VERTEX_COUNT) * 2) * sizeof(float);


}

// Destructeur

Terrain::~Terrain()
{
	// Destruction du VBO

	glDeleteBuffers(1, &m_vboID);


	// Destruction du VAO

	glDeleteVertexArrays(1, &m_vaoID);

	free(m_normals);
	free(m_textCoords);
	free(m_vertices);

}

void Terrain::freeMemory()
{

}

// Getters

float Terrain::getX()
{
	return m_x;
}

float Terrain::getZ()
{
	return m_z;
}

Texture Terrain::getTexture()
{
	return m_texture;
}

GLuint Terrain::getVaoID()
{
	return m_vaoID;
}


// Générateur de terrain

void Terrain::generateTerrain()
{
	int count = VERTEX_COUNT * VERTEX_COUNT;


	m_vertices = (float*)malloc(count * 3 * sizeof(float));
	m_normals = (float*)malloc(count * 3 * sizeof(float));
	m_textCoords = (float*)malloc(count * 2 * sizeof(float));


	m_indices = (int*)malloc((6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT * 1))*sizeof(int));

	


	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			m_vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			m_vertices[vertexPointer * 3 + 1] = 0;
			m_vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1)* SIZE;

			m_normals[vertexPointer * 3] = 0;
			m_normals[vertexPointer * 3 + 1] = 1;
			m_normals[vertexPointer * 3 + 2] = 0;

			m_textCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			m_textCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			m_indices[pointer++] = topLeft;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = bottomRight;
		}
	}
}


void Terrain::charger()
{
	// Destruction d'un éventuel ancien VBO

	if (glIsBuffer(m_vboID) == GL_TRUE)
		glDeleteBuffers(1, &m_vboID);


	// Génération de l'ID

	glGenBuffers(1, &m_vboID);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// Allocation de la mémoire vidéo

	glBufferData(GL_ARRAY_BUFFER, m_tailleVertices + m_tailleNormals + m_tailleTextureCoord, 0, GL_STATIC_DRAW);

	// Transfert des données

	glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVertices, m_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, m_tailleVertices, m_tailleTextureCoord, m_textCoords);
	glBufferSubData(GL_ARRAY_BUFFER, m_tailleTextureCoord, m_tailleNormals, m_normals);

	// Déverrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Destruction d'un éventuel ancien VAO

	if (glIsVertexArray(m_vaoID) == GL_TRUE)
		glDeleteVertexArrays(1, &m_vaoID);


	// Génération de l'ID du VAO

	glGenVertexArrays(1, &m_vaoID);


	// Verrouillage du VAO

	glBindVertexArray(m_vaoID);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// Accès aux vertices dans la mémoire vidéo

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Accès aux coordonnées de texture dans la mémoire vidéo

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVertices));
	glEnableVertexAttribArray(2);

	// Accès aux normales dans la mémoire vidéo

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleTextureCoord));
	glEnableVertexAttribArray(3);



	// Déverrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Déverrouillage du VAO

	glBindVertexArray(0);


}


void Terrain::afficher(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &lightPosition, glm::vec3 &lightColor)
{
	// Activation du shader

	glUseProgram(m_shader.getProgramID());


	// Verrouillage du VAO

	glBindVertexArray(m_vaoID);


	// Envoi des matrices

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
	glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "shineDamper"), 10.0);
	glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "reflectivity"), 1.0);

	// Verouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_texture.getID());


	// Rendu

	//glDrawArrays(GL_TRIANGLES, 0, m_tailleVertices);

	//glDrawElementsBaseVertex(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, 0, 0);

	

	// Déverrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);


	// Déverrouillage du VAO

	glBindVertexArray(0);


	// Désactivation du shader

	glUseProgram(0);
}

// CLASS TERRAINRENDER

// Constructeur 

TerrainRender::TerrainRender() : m_shader("Terrain.vert", "Terrain.frag")
{
	// Activation des rendus des backface
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Activation du shader
	m_shader.charger();


}
// Destructeur
TerrainRender::~TerrainRender()
{

}
// Méthode Render
void TerrainRender::Render(std::list<Terrain> terrains)
{
	for (Terrain terrain : terrains)
	{
		charger(terrain);
		uncharge();
	}
}

void TerrainRender::charger(Terrain terrain)
{
	glBindVertexArray(terrain.getVaoID());
	glEnableVertexAttribArray(0); // Vertex
	glEnableVertexAttribArray(2); // Coordonnés de Texture
	glEnableVertexAttribArray(3); // Normales

	Texture texture = terrain.getTexture();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
}

void TerrainRender::uncharge()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindTexture(GL_TEXTURE_2D, 0);
}