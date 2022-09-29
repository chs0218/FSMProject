#pragma once
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "PizzaStoreOwnerOwnedStates.h"
#include "StateMachine.h"

template <class entity_type>
class State;
struct Telegram;

class PizzaStoreOwner : public BaseGameEntity
{
private:
    StateMachine<PizzaStoreOwner>* m_pStateMachine;
    location_type         m_Location;
public:
    PizzaStoreOwner(int id) : m_Location(home),
        BaseGameEntity(id)
    {
        m_pStateMachine = new StateMachine<PizzaStoreOwner>(this);
        m_pStateMachine->SetCurrentState(PSOStayHomeAndRest::Instance());
    }
    ~PizzaStoreOwner() { delete m_pStateMachine; }

    void Update();
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<PizzaStoreOwner>* GetFSM()const { return m_pStateMachine; }

    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }
};

