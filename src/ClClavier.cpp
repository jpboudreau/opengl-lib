#include "../include/ClClavier.h"

ClClavier* ClClavier::m_instance = nullptr;

ClClavier::ClClavier()
    : m_nombreTouche(500)
{
    m_touche = new TypeEtatTouche[m_nombreTouche];

    for (int i = 0;i < m_nombreTouche; ++i)
        m_touche[i] = TypeEtatTouche::RELACHE;
}

ClClavier::~ClClavier()
{
    delete[] m_touche;
}

ClClavier* ClClavier::Instance()
{
    if (m_instance == nullptr)
        m_instance = new ClClavier();

    return m_instance;
}

ClClavier::TypeEtatTouche ClClavier::EtatTouche(int p_touche)
{
    if (p_touche < 0 || p_touche > m_nombreTouche)
        return TypeEtatTouche::RELACHE;

    return m_touche[p_touche];
}

void ClClavier::ChangerEtatTouche(int p_touche, TypeEtatTouche p_etat)
{
    if (p_touche >= 0 && p_touche <= m_nombreTouche)
        m_touche[p_touche] = p_etat;
}
