#if !defined IMAP_H_INCLUS
#define IMAP_H_INCLUS

class IMap : IDrawable
{
    public :
        explicit IMap();
        virtual ~IMap();

        virtual bool TesterCollisions() const = 0;
};

#endif
