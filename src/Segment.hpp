#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.hpp"

class Segment : public Entity
{
public:
	Segment(b2World *physics, double x1, double y1, double x2, double y2);
	~Segment();

	virtual void onCollision(Entity *other);

	void render(sf::RenderTarget *target);

private:
	b2Vec2 v1, v2;
};

#endif // SEGMENT_HPP
