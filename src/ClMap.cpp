/* ClMap.cpp
 *
 *
 */
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

#include <GLee.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/ClMap.h"
#include "../include/Utilitaire/Utilitaire.h"

using namespace std;

ClMap::ClMap()
{
    ifstream fichier("level1.map");

    if (! fichier.is_open())
        throw "Erreur lors de l'ouverture du fichier";

    string ligne = "";
    const float taille = 10.0f;

    int j = 0;

    while(getline(fichier, ligne))
    {
        vector<ClMap::TypeObjet> tmp;
        for (unsigned int i = 0; i < ligne.size(); ++i)
        {
            if (ligne[i] == '#')
                tmp.push_back(TypeObjet::PLANCHER);
            else if (ligne[i] == 'd')
            {
                tmp.push_back(TypeObjet::POINT_DE_DEPART);
                m_positionDepart.X = j*taille + taille/2;
                m_positionDepart.Y = i*taille + taille/2;
            }
            else if (ligne[i] == '-')
                tmp.push_back(TypeObjet::MUR_HORIZONTALE);
            else if (ligne[i] == '|')
                tmp.push_back(TypeObjet::MUR_VERTICAL);
        }

        m_map.push_back(tmp);
        j++;
    }

    m_textures["sol"] = Utilitaire::ChargerImage("brick.bmp");
    m_textures["mur"] = Utilitaire::ChargerImage("pat-oeil.bmp");
    m_textures["plafond"] = Utilitaire::ChargerImage("ceiling.bmp");
}

ClMap::~ClMap()
{
    for (std::map<string, GLuint>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
        glDeleteTextures( 1, &(it->second) );
}

void ClMap::Dessiner()
{
    const float taille = 10.0f;

    //glColor3f(1.0f, 1.0f, 1.0f);


    for (unsigned int i = 0; i < m_map.size(); ++i)
    {
        for (unsigned int j = 0; j < m_map[i].size(); ++j)
        {
            glBindTexture( GL_TEXTURE_2D, m_textures["sol"] );

            glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);

                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(i*taille, 0.0f, j*taille);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(i*taille + taille, 0.0f, j*taille);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(i*taille + taille, 0.0f, j*taille + taille);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(i*taille, 0.0f, j*taille + taille);
            glEnd();

            glBindTexture( GL_TEXTURE_2D, m_textures["plafond"] );

            glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);

                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(i*taille, 10.0f, j*taille);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(i*taille + taille, 10.0f, j*taille);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(i*taille + taille, 10.0f, j*taille + taille);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(i*taille, 10.0f, j*taille + taille);
            glEnd();

            if (m_map[i][j] == TypeObjet::MUR_HORIZONTALE)
            {
                glBindTexture( GL_TEXTURE_2D, m_textures["mur"] );

                glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);

                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(i*taille, 0.0f, j*taille);

                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(i*taille, 0.0f, j*taille + taille);

                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(i*taille, 10.0f, j*taille + taille);

                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(i*taille, 10.0f, j*taille);
                glEnd();
            }
            else if (m_map[i][j] == TypeObjet::MUR_VERTICAL)
            {
                glBindTexture( GL_TEXTURE_2D, m_textures["mur"] );

                glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);

                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(i*taille + TAILLE/2, 0.0f, j*taille);

                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(i*taille + taille + TAILLE/2, 0.0f, j*taille);

                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(i*taille + taille + TAILLE/2, 10.0f, j*taille);

                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(i*taille + TAILLE/2, 10.0f, j*taille);
                glEnd();
            }
        }
    }

}

void ClMap::TesterCollisions(TypeVecteur2& p_es_position, int p_direction, float p_angleRotation)
{
    unsigned int x = 0;
    unsigned int y = 0;

    x = p_es_position.X / TAILLE;
    y = p_es_position.Y / TAILLE;

    const int tailleBoundingBox = 5;

    int angleRotation = static_cast<float>((abs(static_cast<int>(p_angleRotation*1000)%31415))/1000)>1.5707?1:-1;


    if (x < 0 || x >= m_map.size() || y < 0 || y >= m_map[x].size())
        return;

    if (m_map[x][y] == TypeObjet::MUR_HORIZONTALE)
    {
        if (p_es_position.X > x * TAILLE - tailleBoundingBox && p_es_position.X < x * TAILLE + tailleBoundingBox)
            p_es_position.X -= 0.5f * (float)p_direction;

        /*if (p_es_position.X > x * TAILLE + tailleBoundingBox && p_es_position.X < x * TAILLE - tailleBoundingBox)
            p_es_position.X += 0.5f * (float)m_direction;*/
    }

    if (m_map[x][y] == TypeObjet::MUR_VERTICAL)
    {
        if (p_es_position.Y > y * TAILLE - tailleBoundingBox && p_es_position.Y < y * TAILLE + tailleBoundingBox)
            p_es_position.Y -= 0.5f * (float)angleRotation;

        /*if (p_es_position.X > x * TAILLE + tailleBoundingBox && p_es_position.X < x * TAILLE - tailleBoundingBox)
            p_es_position.X += 0.5f * (float)m_direction;*/
    }
}
