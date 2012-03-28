#ifndef KERN_HPP
#define KERN_HPP

#include "Entity.hpp"
#include <Box2D/Box2D.h>

class Kern : Entity
{
public:
	Kern(b2World *physics);
	void render(sf::RenderTarget *target);
	void onCollision(Entity *other);

	bool isAlive();

};

#endif // KERN_HPP
