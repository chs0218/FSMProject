#pragma once
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "StudentOwnedStates.h"
#include "StateMachine.h"

template <class entity_type> 
class State;
struct Telegram;

const int HungerLevel = 5;
const int StudyLevel = 3;
const int FatigueLevel = 4;

class Student : public BaseGameEntity
{
private:
    StateMachine<Student>* m_pStateMachine;
    location_type         m_Location;

    int                   m_iLeftStudy;
    int                   m_iHungry;
    int                   m_iFatigue;
public:
    Student(int id) : m_Location(home),
        m_iLeftStudy(3),
        m_iHungry(0),
        m_iFatigue(0),
        BaseGameEntity(id)
    {
        m_pStateMachine = new StateMachine<Student>(this);
        //m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
    }
    ~Student() { delete m_pStateMachine; }

    void Update();
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Student>* GetFSM()const { return m_pStateMachine; }

    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    int           StudyLeft()const { return m_iLeftStudy; }
    void          SetStudyLeft(int val) { m_iLeftStudy = val; }
    bool          HaveToStudy()const { return m_iLeftStudy >= StudyLevel; }

    bool          Fatigued() const;
    void          DecreaseFatigue() { m_iFatigue -= 1; }
    void          IncreaseFatigue() { m_iFatigue += 1; }

    bool          Hungry()const;
    void          BuyAndEatPizza() { m_iHungry = 0; }
};

