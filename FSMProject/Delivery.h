#pragma once
#include <string>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "DeliveryOwnedState.h"
#include "StateMachine.h"

template <class entity_type>
class State;
struct Telegram;

const int DeliveryFatigueLevel = 6;

class Delivery : public BaseGameEntity
{
private:
    StateMachine<Delivery>* m_pStateMachine;
    location_type         m_Location;
    int                   m_iFatigue;
    bool                  isStudentOrder;
public:
    Delivery(int id) : m_Location(home),
        isStudentOrder(false),
        BaseGameEntity(id)
    {
        m_pStateMachine = new StateMachine<Delivery>(this);
        m_pStateMachine->SetCurrentState(DeliveryStayHomeAndRest::Instance());
        m_pStateMachine->SetGlobalState(DeliveryGlobalState::Instance());
    }
    ~Delivery() { delete m_pStateMachine; }

    void Update();
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Delivery>* GetFSM()const { return m_pStateMachine; }

    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }
    void ReadyforDeliver(bool IsForStudent);

    bool          Fatigued() const;
    bool          Rested() const;
    bool          IsForStudent() const { return isStudentOrder; }

    void          FinishDeliver(){}
    void          DecreaseFatigue() { m_iFatigue -= 2; }
    void          IncreaseFatigue() { m_iFatigue += 1; }
};

