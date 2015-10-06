#ifndef DEF_SKYBOX
#define DEF_SKYBOX

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

// Macro utile au VBO

#ifndef BUFFER_OFFSET

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif


// Classe Skybox

class Skybox
{
public:

	Skybox(std::string img_Front, std::string img_Back, std::string img_Left, std::string img_Right, std::string img_Top, std::string vertShader, std::string fragShader);
	~Skybox();

	void Afficher(glm::mat4 &projection, glm::mat4 &modelview);
	void Front(glm::mat4 &projection, glm::mat4 &modelview);
	void Back(glm::mat4 &projection, glm::mat4 &modelview);
	void Left(glm::mat4 &projection, glm::mat4 &modelview);
	void Right(glm::mat4 &projection, glm::mat4 &modelview);
	void Top(glm::mat4 &projection, glm::mat4 &modelview);

	void charger();
	void chargerLeft();
	void chargerRight();
	void chargerTop();
	void chargerBack();
	void chargerFront();


private:
	Shader m_Shader;
	Texture m_Front, m_Back, m_Left, m_Right, m_Top;

	float m_Frontvertices[18], m_BackVertices[18], m_LeftVertices[18], m_RightVertices[18], m_TopVertices[18];
	float m_CoordTex[12];

	GLuint m_VboIDTop;
	GLuint m_VboIDLeft;
	GLuint m_VboIDRight;
	GLuint m_VboIDBack;
	GLuint m_VboIDFront;

	GLuint m_VaoIDTop;
	GLuint m_VaoIDLeft;
	GLuint m_VaoIDRight;
	GLuint m_VaoIDBack;
	GLuint m_VaoIDFront;




};


#endif
