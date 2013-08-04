#include <cmath>
#include <iostream>


#include "../include/ClOpenGl.h"
#include "../include/Utilitaire/Utilitaire.h"

using namespace std;

GLfloat	 lightPos[] = { 0.f, 15.0f, 10.0f, 1.0f };

ClOpenGl::ClOpenGl(int *p_pArgc, char* p_pArgv[],
                   const TypeVecteur2& p_dimensionEcran,
                   const string& p_titre,
                    IState *p_pState,
                    Uint32 p_fps,
                   unsigned int p_mode )
                   : m_pEcran(nullptr),m_fps(p_fps), m_pStateManager(new ClStateManager(this)), m_angleX(0.0f), m_angleRotationCamera(0.0f), m_pPolice(nullptr), m_pClavier(ClClavier::Instance()),
                   m_pMap(nullptr), m_direction(-1)
{
    // On initialise la SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw "Erreur lors de l'initialisation de SDL.";

    if (TTF_Init() == -1)
        throw "Erreur lors de l'initialisation de SDL_ttf.";

    m_pPolice = TTF_OpenFont("Ubuntu-B.ttf", 22);

    if (m_pPolice == nullptr)
        throw "Erreur lors du chargement de la police";

    m_pEcran = SDL_SetVideoMode(p_dimensionEcran.X, p_dimensionEcran.Y, 32, p_mode);

    if (m_pEcran == nullptr)
    {
        Fermer();
        throw "Erreur lors de l'initialisation de la video.";
    }

    SDL_WM_SetCaption(p_titre.c_str(), nullptr);

    // Et maintenant OpenGL
    m_pCamera = new ClCamera(p_dimensionEcran.X, p_dimensionEcran.Y,
                            80.0f, 1.0f, 1000.0f);

    glEnable(GL_DEPTH_TEST);
    //glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE);

    // La lumière
    glEnable(GL_LIGHTING);

    GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

    glLightfv(GL_LIGHT0,GL_DIFFUSE,ambientLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);

    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glClearColor(0.2f, 0.9f, 0.9f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glEnable(GL_NORMALIZE);

	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	// On active le blend pour SDL_ttf
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_pStateManager->ChangeState(p_pState);
}

ClOpenGl::~ClOpenGl()
{
    Fermer();
}

void ClOpenGl::Fermer()
{
    delete m_pStateManager;

    for (unsigned int i = 0; i < m_textures.size(); ++i)
        glDeleteTextures( 1, &m_textures[i] );

    if (m_pCamera)
        delete m_pCamera;

    if (m_pEcran != nullptr)
        SDL_FreeSurface(m_pEcran);

    TTF_CloseFont(m_pPolice);
    TTF_Quit();

    SDL_Quit();
}

void ClOpenGl::Run()
{
    bool continuer = true;
    Uint32 tempsActuel = 0;
    Uint32 tempsPrecedent = 0;

    SDL_EnableKeyRepeat(10, 10);

    while (continuer)
    {
        SDL_PollEvent(&m_event);

        switch(m_event.type)
        {
            case SDL_QUIT:
                continuer = false;
                break;

            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                    continuer = false;

                ClClavier::Instance()->ChangerEtatTouche(m_event.key.keysym.sym, ClClavier::TypeEtatTouche::ENFONCE);
            break;

            case SDL_KEYUP:
                ClClavier::Instance()->ChangerEtatTouche(m_event.key.keysym.sym, ClClavier::TypeEtatTouche::RELACHE);
            break;

            default:
            break;
        }

        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent > m_fps)
            tempsPrecedent = tempsActuel;
        else
            SDL_Delay(m_fps - (tempsActuel - tempsPrecedent));

        m_pStateManager->Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode( GL_MODELVIEW);
        glLoadIdentity();

        m_pCamera->Refresh();

        glPushMatrix();
            glEnable(GL_LIGHTING);
            glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
        glPopMatrix();

        m_pStateManager->Draw();
        glFlush();

        SDL_GL_SwapBuffers();
    }
}

void ClOpenGl::WriteText(const std::string& p_texte, const TypeVecteur2& p_position, SDL_Color p_color)
{
    // À vérifier ce n'est pas adéquate
    m_pCamera->ChangeToOrtho();

    // If we don't disable Lightning for text, text will always be black
    //  as it don't get lightning.
    glDisable(GL_LIGHTING);

    Utilitaire::EcrireTexte(m_pPolice, p_color,
                p_position.X, p_position.Y, 0, p_texte);

    glEnable(GL_LIGHTING);

    m_pCamera->ChangeToPerspective();
}


