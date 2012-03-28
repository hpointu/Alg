#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    ContactListener();

	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
	void BeginContact(b2Contact *contact);
};

#endif // CONTACTLISTENER_H
