#pragma once
#include "State.h"

class PizzaStoreOwner;

class PSOGlobalState : public State<PizzaStoreOwner>
{
private:

	PSOGlobalState() {}
	PSOGlobalState(const PSOGlobalState&);
	PSOGlobalState& operator=(const PSOGlobalState&);

public:

	//this is a singleton
	static PSOGlobalState* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO) {}

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO) {}

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);
};

class PSOStayHomeAndRest : public State<PizzaStoreOwner>
{
private:
	PSOStayHomeAndRest() {}
	PSOStayHomeAndRest(const PSOStayHomeAndRest&);
	PSOStayHomeAndRest& operator=(const PSOStayHomeAndRest&);
public:
	static PSOStayHomeAndRest* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO);

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO);

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);
};

class GoPizzaStore : public State<PizzaStoreOwner>
{
private:
	GoPizzaStore() {}
	GoPizzaStore(const GoPizzaStore&);
	GoPizzaStore& operator=(const GoPizzaStore&);
public:
	static GoPizzaStore* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO);

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO);

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);
};

class MakePizza : public State<PizzaStoreOwner>
{
private:

	MakePizza() {}
	MakePizza(const MakePizza&);
	MakePizza& operator=(const MakePizza&);

public:

	static MakePizza* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO);

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO);

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);

};

class RequestDeliver : public State<PizzaStoreOwner>
{
private:

	RequestDeliver() {}
	RequestDeliver(const RequestDeliver&);
	RequestDeliver& operator=(const RequestDeliver&);

public:

	static RequestDeliver* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO);

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO);

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);

};