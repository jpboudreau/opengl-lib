#if !defined CLMAP_H_INCLUS
#define CLMAP_H_INCLUS

#include <vector>
#include <map>
#include <string>

#include "Utilitaire/TypeVecteur2.h"

class ClMap
{
public:
    ClMap();
    ~ClMap();

    enum TypeObjet {PLANCHER, MUR_HORIZONTALE, MUR_VERTICAL, POINT_DE_DEPART};

    void Dessiner();
    TypeVecteur2 PositionDepart() { return m_positionDepart; }
    void TesterCollisions(TypeVecteur2& p_es_position, int p_direction, float p_angleRotation);

private:
    const float TAILLE = 10.0f;

    std::vector<std::vector<TypeObjet>> m_map;
    TypeVecteur2 m_positionDepart;

    std::map<std::string, GLuint> m_textures;
};

#endif
