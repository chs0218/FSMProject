#pragma once
#include "State.h"

class Student;
class StudentGlobalState : public State<Student>
{
private:
	StudentGlobalState() {}
	StudentGlobalState(const StudentGlobalState&);
	StudentGlobalState& operator=(const StudentGlobalState&);

public:

	//this is a singleton
	static StudentGlobalState* Instance();

	virtual void Enter(Student* pStudent) {}

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent) {}

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class StayHomeAndRest : public State<Student>
{
private:
	StayHomeAndRest(){}
	StayHomeAndRest(const StayHomeAndRest&);
	StayHomeAndRest& operator=(const StayHomeAndRest&);
public:
	static StayHomeAndRest* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class CallAndTalkToParent : public State<Student>
{
private:
	CallAndTalkToParent() {}
	CallAndTalkToParent(const CallAndTalkToParent&);
	CallAndTalkToParent& operator=(const CallAndTalkToParent&);
public:
	static CallAndTalkToParent* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class OrderPizza : public State<Student>
{
private:
	OrderPizza() {}
	OrderPizza(const OrderPizza&);
	OrderPizza& operator=(const OrderPizza&);
public:
	static OrderPizza* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class WaitAndEatPizza : public State<Student>
{
private:
	WaitAndEatPizza() {}
	WaitAndEatPizza(const WaitAndEatPizza&);
	WaitAndEatPizza& operator=(const WaitAndEatPizza&);
public:
	static WaitAndEatPizza* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class PlayGame : public State<Student>
{
private:
	PlayGame() {}
	PlayGame(const PlayGame&);
	PlayGame& operator=(const PlayGame&);
public:
	static PlayGame* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class GoLibraryAndStudy : public State<Student>
{
private:
	GoLibraryAndStudy() {}
	GoLibraryAndStudy(const PlayGame&);
	GoLibraryAndStudy& operator=(const PlayGame&);
public:
	static GoLibraryAndStudy* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};