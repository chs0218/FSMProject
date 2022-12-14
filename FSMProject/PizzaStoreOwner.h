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

const int PSOFatigueLevel = 10;

class PizzaStoreOwner : public BaseGameEntity
{
private:
    StateMachine<PizzaStoreOwner>* m_pStateMachine;
    location_type         m_Location;
    int                   m_iFatigue;
    bool                  isStudentOrder;
    bool                  m_iCooking;
public:
    PizzaStoreOwner(int id) : m_Location(home),
        isStudentOrder(false),
        m_iCooking(false),
        BaseGameEntity(id)
    {
        m_pStateMachine = new StateMachine<PizzaStoreOwner>(this);
        m_pStateMachine->SetCurrentState(PSOStayHomeAndRest::Instance());
        m_pStateMachine->SetGlobalState(PSOGlobalState::Instance());
    }
    ~PizzaStoreOwner() { delete m_pStateMachine; }

    void Update();
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<PizzaStoreOwner>* GetFSM()const { return m_pStateMachine; }

    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }
   

    bool          Fatigued() const;
    bool          Rested() const;

    void          ReadyForOrder() { isStudentOrder = false; };

    void          GetOrder(bool IsForStudent);
    bool          IsForStudent() const { return isStudentOrder; }
    bool          IsCooking() const { return m_iCooking; }
    void          SetCooking() { m_iCooking = true; }
    void          FinishCooking() { m_iCooking = false; }

    void          DecreaseFatigue() { m_iFatigue -= 2; }
    void          IncreaseFatigue() { m_iFatigue += 1; }
};

