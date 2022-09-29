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

class GetPizzaOrder : public State<PizzaStoreOwner>
{
private:

	GetPizzaOrder() {}
	GetPizzaOrder(const GetPizzaOrder&);
	GetPizzaOrder& operator=(const GetPizzaOrder&);

public:

	static GetPizzaOrder* Instance();

	virtual void Enter(PizzaStoreOwner* pPSO);

	virtual void Execute(PizzaStoreOwner* pPSO);

	virtual void Exit(PizzaStoreOwner* pPSO);

	virtual bool OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg);

};
