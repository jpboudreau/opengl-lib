#if !defined CL_OPENGL_INCLUS
#define CL_OPENGL_INCLUS

#include <GLee.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>


// TODO : À mieux architecturisé
#include "ClOpenGl.h"
#include "ClMap.h"
#include "ClClavier.h"
#include "ClCamera.h"

#include "Interfaces/IActualisable.h"
#include "Interfaces/IDrawable.h"
#include "Interfaces/IMap.h"

#include "Utilitaire/Utilitaire.h"
#include "Utilitaire/TypeVecteur2.h"
#include "Utilitaire/Vector3.h"

class ClOpenGl
{
public :
    ClOpenGl(int *p_pArgc, char** p_pArgv,
            const TypeVecteur2& p_dimension,
            const std::string& p_titre,
            Uint32 p_fps = 30,
            unsigned int p_mode = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

    virtual ~ClOpenGl();

    void Run();

private :
    // On ferme tout ce qu'on à ouvert
    void Fermer();

    /*****
     * ChangerDimension : Sera appellé lorsque la fenêtre changera de dimension.
     */
    void ChangerDimension(int p_largeur, int p_hauteur);

    virtual void Draw();
    virtual void Update();

    void EcrireTexte(const std::string& p_texte, const TypeVecteur2& p_position);
    void Perspective();
    void Ortho();


    SDL_Surface *m_pEcran;
    SDL_Event m_event;
    Uint32 m_fps;

    ClCamera *m_pCamera;

    float m_angleX;
    float m_angleRotationCamera;
    float m_positionVerticale;
    TypeVecteur2 m_positionHorizontale;
    TTF_Font *m_pPolice;
    ClClavier *m_pClavier;
    ClMap *m_pMap;

    std::vector<GLuint> m_textures;

    int m_direction;

protected:
    ClCamera& Camera() { return *m_pCamera; }
    ClClavier& Keyboard() { return *m_pClavier; }
};

#endif
