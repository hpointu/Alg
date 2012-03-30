#include "Segment.hpp"
#include "const.hpp"
#include "EntityManager.hpp"
#include <cmath>

Segment::Segment(b2World *physics, double x1, double y1, double x2, double y2) :
	Entity(physics),
	v1(x1/SCALE, -y1/SCALE),
	v2(x2/SCALE, -y2/SCALE)
{
	b2BodyDef def;
	def.position.Set(0,0);

	b2EdgeShape edge;
	edge.Set(v1, v2);

	body = physics->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &edge;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);
}

Segment::~Segment()
{
}

void Segment::onCollision(Entity *other)
{
	EntityManager::getInstance()->enqueueToDelete(this);
	EntityManager::getInstance()->enqueueToDelete(other);
}

void Segment::render(sf::RenderTarget *target)
{
	if(body)
	{
		double a = v2.y - v1.y;
		double b = v2.x - v1.x;
		double length = ::sqrt( (a*a) + (b*b) );
		double radangle = ::acos(b/length);
		double angle = radangle*180/M_PI;
		if(v2.y < v1.y)
			angle *= -1;

		sf::RectangleShape line(sf::Vector2f(length, 1.f/SCALE));
		line.setFillColor(sf::Color::Black);
		line.setPosition(v1.x, -v1.y);
		line.rotate(-angle);

		target->draw(line);
	}
}
