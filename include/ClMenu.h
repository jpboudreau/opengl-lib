#if !defined CL_MENU_INCLUS
#define CL_MENU_INCLUS

#include "../ClOpenGl.h"

class ClMenu : public IState
{
    public :
        explicit ClMenu();
        ~ClMenu();

        /* virtual */ void Draw(ClOpenGl&) const;
        /* virtual */ void Update();
        /* virtual */ void Initialize();
};

#endif
