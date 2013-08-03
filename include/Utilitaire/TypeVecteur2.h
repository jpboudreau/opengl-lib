#if !defined CLVECTEUR2_H_INCLUS
#define CLVECTEUR2_H_INCLUS

struct TypeVecteur2
{
    TypeVecteur2()
        : X(0.0f), Y(0.0f)
    {
    }

    TypeVecteur2(float p_x, float p_y)
        : X(p_x), Y(p_y)
    {
    }

    float X;
    float Y;
};

#endif
