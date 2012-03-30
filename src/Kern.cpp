#include "Kern.hpp"
#include "const.hpp"
#include "EntityManager.hpp"

Kern::Kern(b2World *physics) :
	Entity(physics),
	pv(5)
{
	b2BodyDef def;
	def.position.Set(0,0);

	b2CircleShape circle;
	circle.m_radius = 10.f/SCALE;

	body = physics->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);
}

void Kern::onCollision(Entity *other)
{
	EntityManager::getInstance()->enqueueToDelete(other);

	pv--;
	if(pv <= 0)
		dead = true;
}

bool Kern::isAlive()
{
	return !dead;
}

void Kern::render(sf::RenderTarget *target)
{
	if(body)
	{
		sf::Color col = dead ? sf::Color(180, 0, 0, 200) : sf::Color(0, 180, 0, 200);
		sf::CircleShape shape;
		shape.setRadius(10.f/SCALE);
		shape.setPosition(-10.f/SCALE,-10.f/SCALE);
		shape.setFillColor(col);
		target->draw(shape);
	}
}
