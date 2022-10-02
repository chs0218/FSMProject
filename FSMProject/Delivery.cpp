#include "Delivery.h"

bool Delivery::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Delivery::Update()
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    m_pStateMachine->Update();
}

bool Delivery::Fatigued() const
{
    if (m_iFatigue > DeliveryFatigueLevel)
    {
        return true;
    }

    return false;
}

bool Delivery::Rested() const
{
    if (m_iFatigue < 1)
    {
        return true;
    }
    return false;
}

void Delivery::ReadyforDeliver(bool IsForStudent)
{
    isStudentOrder = IsForStudent;
}
