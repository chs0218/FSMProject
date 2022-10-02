#pragma once
#include "State.h"
class Delivery;

class DeliveryGlobalState : public State<Delivery>
{
private:
	DeliveryGlobalState() {}
	DeliveryGlobalState(const DeliveryGlobalState&);
	DeliveryGlobalState& operator=(const DeliveryGlobalState&);
public:
	//this is a singleton
	static DeliveryGlobalState* Instance();

	virtual void Enter(Delivery* pDelivery) {}

	virtual void Execute(Delivery* pDelivery);

	virtual void Exit(Delivery* pDelivery) {}

	virtual bool OnMessage(Delivery* pDelivery, const Telegram& msg);
};

class DeliveryStayHomeAndRest : public State<Delivery>
{
private:
	DeliveryStayHomeAndRest() {}
	DeliveryStayHomeAndRest(const DeliveryStayHomeAndRest&);
	DeliveryStayHomeAndRest& operator=(const DeliveryStayHomeAndRest&);
public:
	static DeliveryStayHomeAndRest* Instance();

	virtual void Enter(Delivery* pDelivery);

	virtual void Execute(Delivery* pDelivery);

	virtual void Exit(Delivery* pDelivery);

	virtual bool OnMessage(Delivery* pDelivery, const Telegram& msg);
};

class WaitDeliveryRequest : public State<Delivery>
{
private:
	WaitDeliveryRequest() {}
	WaitDeliveryRequest(const WaitDeliveryRequest&);
	WaitDeliveryRequest& operator=(const WaitDeliveryRequest&);
public:
	static WaitDeliveryRequest* Instance();

	virtual void Enter(Delivery* pDelivery);

	virtual void Execute(Delivery* pDelivery);

	virtual void Exit(Delivery* pDelivery);

	virtual bool OnMessage(Delivery* pDelivery, const Telegram& msg);
};

class GoDeliver : public State<Delivery>
{
private:
	GoDeliver() {}
	GoDeliver(const GoDeliver&);
	GoDeliver& operator=(const GoDeliver&);
public:
	static GoDeliver* Instance();

	virtual void Enter(Delivery* pDelivery);

	virtual void Execute(Delivery* pDelivery);

	virtual void Exit(Delivery* pDelivery);

	virtual bool OnMessage(Delivery* pDelivery, const Telegram& msg);
};