#pragma once
#include "State.h"

class PizzaStoreOwner;
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

