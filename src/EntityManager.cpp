#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

void EntityManager::enqueueToDelete(Entity *e)
{
	toDelete.push_back(e);
}

void EntityManager::deleteQueue()
{
	std::sort(toDelete.begin(), toDelete.end());
	unsigned int i = 0;
	while(i<toDelete.size())
	{
		Entity *e = toDelete.at(i++);
		while(i<toDelete.size() && toDelete.at(i) == e)
			++i;
		e->deleteMe();
	}
	toDelete.clear();
}
