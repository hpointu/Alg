#include "ContactListener.hpp"
#include <iostream>
#include "Entity.hpp"

ContactListener::ContactListener()
{

}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

}

void ContactListener::BeginContact(b2Contact *contact)
{
	Entity *e1 = (Entity*) contact->GetFixtureA()->GetUserData();
	Entity *e2 = (Entity*) contact->GetFixtureB()->GetUserData();

	e1->onCollision(e2);
	e2->onCollision(e1);
}
