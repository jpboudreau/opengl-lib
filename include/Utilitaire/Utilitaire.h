#if !defined UTILITAIRE_H_INCLUS
#define UTILITAIRE_H_INCLUS

#include <GL/gl.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

namespace Utilitaire
{
/****
 * ChargerImage : Permet de charger une image à l'aide de SDL et retourne l'ID de la texture OpenGL
 */
GLuint ChargerImage(std::string p_cheminImage);

void EcrireTexte(const TTF_Font *Font, SDL_Color p_couleur,
                const double& X, const double& Y, const double& Z,  const std::string& Text);
}
#endif
