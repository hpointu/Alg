#include "Segment.hpp"
#include "const.hpp"
#include "EntityManager.hpp"
#include <cmath>

Segment::Segment(b2World *physics, double x1, double y1, double x2, double y2) :
	Entity(physics),
	v1(x1, -y1),
	v2(x2, -y2)
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
		double a = v2.y/SCALE - v1.y/SCALE;
		double b = v2.x/SCALE - v1.x/SCALE;
		double length = ::sqrt( (a*a) + (b*b) );
		double radangle = ::acos(b/length);
		double angle = radangle*180/M_PI;

		sf::RectangleShape line(sf::Vector2f(length, 0.5/SCALE));
		line.setFillColor(sf::Color::Black);
		line.setPosition(v1.x/SCALE, -v1.y/SCALE);
		line.rotate(-angle);

		target->draw(line);
	}
}
