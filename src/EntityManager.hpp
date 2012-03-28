#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Singleton.hpp"
#include "Entity.hpp"

#include <vector>

class EntityManager : public Singleton<EntityManager>
{
	friend class Singleton<EntityManager>;

public:
	void enqueueToDelete(Entity *e);
	void deleteQueue();

private:
	EntityManager();
	std::vector<Entity*> toDelete;

};

#endif // ENTITYMANAGER_HPP
