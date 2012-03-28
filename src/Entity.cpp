#include "Entity.hpp"
#include <iostream>

Entity::Entity(b2World *physics) :
	dead(false),
	physics(physics)
{
}

void Entity::onCollision(Entity *)
{
	dead = true;
}

void Entity::deleteMe()
{
	if(body)
	{
		physics->DestroyBody(body);
	}
	body = NULL;
}
