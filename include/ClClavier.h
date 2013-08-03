#if !defined CLCLAVIER_H_INCLUS
#define CLCLAVIER_H_INCLUS

class ClClavier
{
public:
    static ClClavier* Instance();

    enum TypeEtatTouche {ENFONCE, RELACHE};

    TypeEtatTouche EtatTouche(int p_touche);
    void ChangerEtatTouche(int p_touche, TypeEtatTouche p_etat);

    ~ClClavier();

private:
    ClClavier();

    static ClClavier* m_instance;
    TypeEtatTouche* m_touche;

    int m_nombreTouche;
};

#endif
