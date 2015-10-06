#include "Skybox.h"
#include "Texture.h"


// Constructeur 

Skybox::Skybox(std::string img_Front, std::string img_Back, std::string img_Left, std::string img_Right, std::string img_Top, std::string vertShader, std::string fragShader) : m_Front(img_Front),
m_Back(img_Back),
m_Left(img_Left),
m_Right(img_Right),
m_Top(img_Top),
m_Shader(vertShader, fragShader)

{
	// Chargement du Shader

	m_Shader.charger();

	// Chargements des textures

	m_Front.charger();
	m_Back.charger();
	m_Left.charger();
	m_Right.charger();
	m_Top.charger();

	// Tableau de coordonn�e de texture

	float FrontTexCoord[] = {
						0,0,  0,1,   1,1,
						0,0,  1,0,   1,1};



	// Cr�ation de la SKybox

	float facefront[] = { 
		0.0, 0.0, -50.0,      0.0, 50.0, -50.0,    50.0, 50.0, -50.0,
		0.0, 0.0, -50.0,      50.0, 0.0, -50.0,    50.0, 50.0, -50.0 };

	float faceBack[] = {
		0.0, 0.0, 0.0,      0.0, 50.0,0.0,          50.0, 50.0,0.0,
		0.0, 0.0, 0.0,     50.0, 0.0,0.0,           50.0, 50.0, 0.0 };

	float faceLeft[] = {
			0.0, 0.0, 0.0,   0.0,50.0,0.0,   0.0,50.0,-50.0,
			0.0,0.0,0.0,    0.0,0.0,-50.0,  0.0,50.0,-50.0
	};

	float faceRight[] = {
		50.0, 0.0, 0.0, 50.0, 50.0, 0.0, 50.0, 50.0, -50.0,
		50.0, 0.0, 0.0, 50.0, 0.0, -50.0, 50.0, 50.0, -50.0
	};

	float faceTop[] = {
		0.0, 50.0, 0.0, 0.0, 50.0, -50.0, 50.0, 50.0, -50.0,
		0.0, 50.0, 0.0, 50.0, 50.0, 0.0, 50.0, 50.0, -50.0
	};


	for (int i = 0; i < 18; i++)
	{
		m_Frontvertices[i] = facefront[i];
		m_BackVertices[i] = faceBack[i];
		m_LeftVertices[i] = faceLeft[i];
		m_RightVertices[i] = faceRight[i];
		m_TopVertices[i] = faceTop[i];
	}

	for (int i = 0; i < 12; i++)
		m_CoordTex[i] = FrontTexCoord[i];

}

Skybox::~Skybox()
{

}

void Skybox::charger()
{
	chargerTop();
	chargerLeft();
	chargerBack();
	chargerRight();
	chargerFront();
}

void Skybox::chargerTop()
{
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(m_VboIDTop) == GL_TRUE)
		glDeleteBuffers(1, &m_VboIDTop);


	// G�n�ration de l'ID

	glGenBuffers(1, &m_VboIDTop);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDTop);


	// Allocation de la m�moire vid�o

	glBufferData(GL_ARRAY_BUFFER, 18*sizeof(float) + 12*sizeof(float), 0, GL_STATIC_DRAW);


	// Transfert des donn�es

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(float),m_TopVertices);
	glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(float), 12 * sizeof(float), m_CoordTex);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(m_VaoIDTop) == GL_TRUE)
		glDeleteVertexArrays(1, &m_VaoIDTop);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &m_VaoIDTop);


	// Verrouillage du VAO

	glBindVertexArray(m_VaoIDTop);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDTop);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// D�verrouillage du VAO

	glBindVertexArray(0);
}

void Skybox::chargerLeft()
{
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(m_VboIDLeft) == GL_TRUE)
		glDeleteBuffers(1, &m_VboIDLeft);


	// G�n�ration de l'ID

	glGenBuffers(1, &m_VboIDLeft);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDLeft);


	// Allocation de la m�moire vid�o

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float) + 12 * sizeof(float), 0, GL_STATIC_DRAW);


	// Transfert des donn�es

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(float), m_LeftVertices);
	glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(float), 12 * sizeof(float), m_CoordTex);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(m_VaoIDLeft) == GL_TRUE)
		glDeleteVertexArrays(1, &m_VaoIDLeft);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &m_VaoIDLeft);


	// Verrouillage du VAO

	glBindVertexArray(m_VaoIDLeft);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDLeft);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// D�verrouillage du VAO

	glBindVertexArray(0);
}
void Skybox::chargerRight()
{
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(m_VboIDRight) == GL_TRUE)
		glDeleteBuffers(1, &m_VboIDRight);


	// G�n�ration de l'ID

	glGenBuffers(1, &m_VboIDRight);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDRight);


	// Allocation de la m�moire vid�o

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float) + 12 * sizeof(float), 0, GL_STATIC_DRAW);


	// Transfert des donn�es

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(float), m_RightVertices);
	glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(float), 12 * sizeof(float), m_CoordTex);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(m_VaoIDRight) == GL_TRUE)
		glDeleteVertexArrays(1, &m_VaoIDRight);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &m_VaoIDRight);


	// Verrouillage du VAO

	glBindVertexArray(m_VaoIDRight);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDRight);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// D�verrouillage du VAO

	glBindVertexArray(0);
}

void Skybox::chargerFront()
{
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(m_VboIDFront) == GL_TRUE)
		glDeleteBuffers(1, &m_VboIDFront);


	// G�n�ration de l'ID

	glGenBuffers(1, &m_VboIDFront);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDFront);


	// Allocation de la m�moire vid�o

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float) + 12 * sizeof(float), 0, GL_STATIC_DRAW);


	// Transfert des donn�es

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(float), m_Frontvertices);
	glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(float), 12 * sizeof(float), m_CoordTex);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(m_VaoIDFront) == GL_TRUE)
		glDeleteVertexArrays(1, &m_VaoIDFront);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &m_VaoIDFront);


	// Verrouillage du VAO

	glBindVertexArray(m_VaoIDFront);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDFront);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// D�verrouillage du VAO

	glBindVertexArray(0);
}

void Skybox::chargerBack()
{
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(m_VboIDBack) == GL_TRUE)
		glDeleteBuffers(1, &m_VboIDBack);


	// G�n�ration de l'ID

	glGenBuffers(1, &m_VboIDBack);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDBack);


	// Allocation de la m�moire vid�o

	glBufferData(GL_ARRAY_BUFFER, (18 * sizeof(float)) + (12 * sizeof(float)), 0, GL_STATIC_DRAW);


	// Transfert des donn�es

	glBufferSubData(GL_ARRAY_BUFFER, 0, (18 * sizeof(float)), m_BackVertices);
	glBufferSubData(GL_ARRAY_BUFFER, (18 * sizeof(float)), 12 * sizeof(float), m_CoordTex);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(m_VaoIDBack) == GL_TRUE)
		glDeleteVertexArrays(1, &m_VaoIDBack);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &m_VaoIDBack);


	// Verrouillage du VAO

	glBindVertexArray(m_VaoIDBack);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, m_VboIDBack);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// D�verrouillage du VAO

	glBindVertexArray(0);
}




void Skybox::Afficher(glm::mat4 &projection, glm::mat4 &modelview)
{

	// Rendu

	glDepthMask(0);

	Front(projection,modelview);
	Back(projection, modelview);
	Left(projection, modelview);
	Right(projection, modelview);
	Top(projection, modelview);

	glDepthMask(1);

	
}

void Skybox::Front(glm::mat4 &projection, glm::mat4 &modelview)
{
	glUseProgram(m_Shader.getProgramID());
	// Verrouillage VAO
	glBindVertexArray(m_VaoIDFront);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_Front.getID());


	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0 * 4, 6);

	

	// D�verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);

	// D�sactivation des tableaux
	


	glBindVertexArray(0);

	glUseProgram(0);
}





void Skybox::Back(glm::mat4 &projection, glm::mat4 &modelview)
{
	glUseProgram(m_Shader.getProgramID());
	// Verrouillage VAO
	glBindVertexArray(m_VaoIDBack);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_Back.getID());



	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// D�verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);



	// D�sactivation des tableaux



	// Deverrouillage VAO
	glBindVertexArray(0);
	glUseProgram(0);
}

void Skybox::Left(glm::mat4 &projection, glm::mat4 &modelview)
{
	glUseProgram(m_Shader.getProgramID());
	// Verrouillage VAO
	glBindVertexArray(m_VaoIDLeft);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_Left.getID());

	// D�sactiver le Depth Buffer

	//glDisable(GL_DEPTH_TEST);

	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glEnable(GL_DEPTH_TEST);

	// D�verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);

	// Deverrouillage VAO
	glBindVertexArray(0);

	glUseProgram(0);
}

void Skybox::Right(glm::mat4 &projection, glm::mat4 &modelview)
{
	glUseProgram(m_Shader.getProgramID());
	// Verrouillage VAO
	glBindVertexArray(m_VaoIDRight);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_Right.getID());



	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// D�verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);



	// D�sactivation des tableaux


	// Deverrouillage VAO
	glBindVertexArray(0);
	glUseProgram(0);
}

void Skybox::Top(glm::mat4 &projection, glm::mat4 &modelview)
{
	glUseProgram(m_Shader.getProgramID());
	// Verrouillage VAO
	glBindVertexArray(m_VaoIDTop);

	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_Top.getID());



	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glBindTexture(GL_TEXTURE_2D, 0);


	// Deverrouillage VAO
	glBindVertexArray(0);
	glUseProgram(0);

}