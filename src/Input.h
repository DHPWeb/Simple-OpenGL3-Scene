#ifndef DEF_INPUT
#define DEF_INPUT

// Include

#include <SDL2\SDL.h>


// Classe

class Input
{
public:

	Input();
	~Input();

	void updateEvenements();

	bool getTouche(const SDL_Scancode touche) const;
	bool getBoutonSouris(const Uint8 bouton) const;
	bool mouvementSouris() const;

	void afficherPointeur(bool reponse) const;
	void capturePointeur(bool reponse) const;

	bool terminer() const;

	// Getters

	int getX() const;
	int getY() const;

	int getXRel() const;
	int getYRel() const;

private:

	SDL_Event m_evenements;
	bool m_touches[SDL_NUM_SCANCODES];
	bool m_boutonsSouris[8];

	int m_x;
	int m_y;
	int m_xRel;
	int m_yRel;

	bool m_terminer;
};

#endif

