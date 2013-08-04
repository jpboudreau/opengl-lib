#if !defined CL_STATEMANAGER_INCLUS
#define CL_STATEMANAGER_INCLUS

#include <vector>

#include "Interfaces/IState.h"
#include "ClOpenGl.h"

class ClOpenGl;

/*****
 * Will handle state management.
 ****/
class ClStateManager
{
    public :
        ClStateManager(ClOpenGl* p_pGameManager);
        ~ClStateManager();

        void Draw();
        void Update();

        void ChangeState(IState* p_pState);

    private :
        IState* m_pCurrentState;
        ClOpenGl* m_pGameManager;
};

#endif
