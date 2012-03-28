#include "Entity.hpp"
#include <iostream>

#include "EntityManager.hpp"

Entity::Entity(b2World *physics) :
	dead(false),
	physics(physics)
{
}

void Entity::onCollision(Entity *)
{
}

void Entity::deleteMe()
{
	if(body)
	{
		physics->DestroyBody(body);
	}
	body = NULL;
}
