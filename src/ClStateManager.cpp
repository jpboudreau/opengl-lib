#include "../include/ClStateManager.h"

ClStateManager::ClStateManager(ClOpenGl* p_pGameManager)
    : m_pCurrentState(nullptr), m_pGameManager(p_pGameManager)
{
}

ClStateManager::~ClStateManager()
{
    if (m_pCurrentState != nullptr)
        delete m_pCurrentState;
}

void ClStateManager::Draw()
{
    m_pCurrentState->Draw(*m_pGameManager);
}

void ClStateManager::Update()
{
    m_pCurrentState->Update();
}

void ClStateManager::ChangeState(IState* p_pState)
{
    if (m_pCurrentState == nullptr)
    {
        m_pCurrentState = p_pState;
        m_pCurrentState->StateManager(this);
        m_pCurrentState->Initialize();
    }
}
