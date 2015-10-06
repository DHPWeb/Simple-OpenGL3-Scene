#ifndef DEF_TEXTURES
#define DEF_TEXTURES

// Include OpenGL

#include <gl\glew.h>

// Include SDL

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

// Includes

#include <iostream>
#include <string>

// Classe Texture

class Textures
{
public:

	Textures(std::string fichierImage);
	Textures();
	~Textures();

	bool charger();
	GLuint getID() const;

	void setFichierImage(const std::string &fichierImage);
	SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

	Textures(Textures const &textureACopier);
	Textures& operator=(Textures const &textureACopier);

private:

	GLuint m_id;
	std::string m_fichierImage;
};

#endif