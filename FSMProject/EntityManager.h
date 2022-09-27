#pragma once
#include <map>
#include <cassert>
#include <string>

class BaseGameEntity;

//provide easy access
#define EntityMgr EntityManager::Instance()

class EntityManager
{
private:
	typedef std::map<int, BaseGameEntity*> EntityMap;
private:
	EntityMap m_EntityMap;

	EntityManager() {}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
public:
	static EntityManager* Instance();
	void RegisterEntity(BaseGameEntity* NewEntity);
	BaseGameEntity* GetEntityFromID(int id) const;
	void RemoveEntity(BaseGameEntity* pEntity);
};

