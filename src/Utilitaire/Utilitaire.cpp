#include "../../include/Utilitaire/Utilitaire.h"

namespace Utilitaire
{

GLuint ChargerImage(std::string p_cheminImage)
{
    SDL_Surface *surface = nullptr;

    if (! (surface = SDL_LoadBMP(p_cheminImage.c_str())))
        throw "Erreur lors de l'initialisation du chargement de : " + p_cheminImage;

    GLint nbCouleur = surface->format->BytesPerPixel;

    GLenum formatTexture;

    if (nbCouleur == 4)     // contains an alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            formatTexture = GL_RGBA;
        else
            formatTexture = GL_BGRA;
    }//
    else if (nbCouleur == 3)     // no alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            formatTexture = GL_RGB;
        else
            formatTexture = GL_BGR;
    }
    else
        throw "Erreur, pas le bon nombre de couleur?";

    GLuint texture;
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );

	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nbCouleur, surface->w, surface->h, 0,
                      formatTexture, GL_UNSIGNED_BYTE, surface->pixels );

    // On n'a plus besoin de la surface
    SDL_FreeSurface( surface );

    return texture;
}

void EcrireTexte(const TTF_Font *Font, SDL_Color p_couleur,
                const double& X, const double& Y, const double& Z,  const std::string& Text)
{
	SDL_Surface *Message = TTF_RenderText_Blended(const_cast<TTF_Font*>(Font), Text.c_str(), p_couleur);
	unsigned Texture = 0;


	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA,
	             GL_UNSIGNED_BYTE, Message->pixels);

    glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3d(X, Y, Z);
		glTexCoord2d(1, 0); glVertex3d(X+Message->w, Y, Z);
		glTexCoord2d(1, 1); glVertex3d(X+Message->w, Y+Message->h, Z);
		glTexCoord2d(0, 1); glVertex3d(X, Y+Message->h, Z);
	glEnd();

	glDeleteTextures(1, &Texture);
	SDL_FreeSurface(Message);
}
}
