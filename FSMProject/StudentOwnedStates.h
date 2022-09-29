#pragma once
#include "State.h"

class Student;
class StayHomeAndRest : public State<Student>
{
private:
	StayHomeAndRest(){}
	StayHomeAndRest(const StayHomeAndRest&);
	StayHomeAndRest& operator=(const StayHomeAndRest&);
public:
	//this is a singleton
	static StayHomeAndRest* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

