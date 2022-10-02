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

bool PizzaStoreOwner::Fatigued() const
{
    if (m_iFatigue > PSOFatigueLevel)
    {
        return true;
    }

    return false;
}

bool PizzaStoreOwner::Rested() const
{
    if (m_iFatigue < 1)
    {
        return true;
    }
    return false;
}

void PizzaStoreOwner::GetOrder(bool IsForStudent)
{
    isStudentOrder = IsForStudent;
}