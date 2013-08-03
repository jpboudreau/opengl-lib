#if !defined IDESSINABLE_H_INCLUS
#define IDESSINABLE_H_INCLUS

/*****
 *  Représente un type dessinable à l'écran
 */
class IDrawable
{
    public :
        explicit IDrawable() {};
        virtual ~IDrawable() {};

        virtual void Draw() const = 0;

    //private :
};

#endif
