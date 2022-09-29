#include "Student.h"

bool Student::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}


void Student::Update()
{
    SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

    m_pStateMachine->Update();
}

bool Student::Hungry() const
{
    if (m_iHungry > HungerLevel)
    {
        return true;
    }
    return false;
}

bool Student::Fatigued() const
{
    if (m_iFatigue > FatigueLevel)
    {
        return true;
    }

    return false;
}

bool Student::Rested() const
{
    if (m_iFatigue < 1)
    {
        return true;
    }
    return false;
}