#include "Segment.hpp"
#include "const.hpp"
#include "EntityManager.hpp"
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
		sf::Shape shape = sf::Shape::Line(v1.x, -v1.y, v2.x, -v2.y,
													 1.f/SCALE, sf::Color::Black);
		target->Draw(shape);
	}
}
