#if !defined CLVECTEUR3_H_INCLUS
#define CLVECTEUR3_H_INCLUS

struct Vector3
{
    Vector3()
        : X(0.0f), Y(0.0f), Z(0.0f)
    {
    }

    Vector3(float p_x, float p_y = 0.0f, float p_z = 0.0f)
        : X(p_x), Y(p_y), Z(p_z)
    {
    }

    float X;
    float Y;
    float Z;
};

#endif
