#include "PizzaStoreOwner.h"

bool PizzaStoreOwner::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}


void PizzaStoreOwner::Update()
{
    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    m_pStateMachine->Update();
}