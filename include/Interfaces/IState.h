#if !defined ISTATE_INCLUS
#define ISTATE_INCLUS

#include "../ClStateManager.h"

class ClStateManager;
class ClOpenGl;

class IState
{
    public :
        explicit IState() {};
        virtual ~IState() {};

        virtual void Draw(ClOpenGl&) const = 0;
        virtual void Update() = 0;
        virtual void Initialize() = 0;

        void StateManager(ClStateManager* p_pStateManager)
            { m_pStateManager = p_pStateManager; }

    protected :
        ClStateManager* m_pStateManager;
};

#endif
