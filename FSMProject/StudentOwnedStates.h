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
	static StayHomeAndRest* Instance();

	virtual void Enter(Student* pStudent);

	virtual void Execute(Student* pStudent);

	virtual void Exit(Student* pStudent);

	virtual bool OnMessage(Student* pStudent, const Telegram& msg);
};

class EatPizza : public State<Student>
{
private:
	EatPizza() {}
	EatPizza(const EatPizza&);
	EatPizza& operator=(const EatPizza&);
public:
	static EatPizza* Instance();

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