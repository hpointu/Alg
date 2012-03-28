#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(b2World *physics);

	virtual void onCollision(Entity *other);

	virtual void deleteMe();

	virtual void render(sf::RenderTarget *target) = 0;
	bool dead;

protected:
	b2World *physics;
	b2Body *body;
};

#endif // ENTITY_H
