#include "Particle.hpp"
#include "const.hpp"
#include <iostream>

Particle::Particle(b2World *physics, double x, double y, double ix, double iy) :
	Entity(physics)
{
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(x,y);

	b2CircleShape circle;
	circle.m_radius = 1.5/SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 10.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = this;

	body = physics->CreateBody(&def);
	body->CreateFixture(&fixtureDef);

	// give random initial impulse
	b2Vec2 vect(ix, iy);
//	vect = b2Vec2(-3, 0);
	body->ApplyLinearImpulse(vect, body->GetWorldCenter());
}

Particle::~Particle()
{
}

void Particle::render(sf::RenderTarget *target)
{
	if(body)
	{
		sf::CircleShape shape;
		shape.setRadius(1.5f/SCALE);
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(body->GetPosition().x-(1.5f/SCALE),
								-body->GetPosition().y-(1.5f/SCALE));

		target->draw(shape);
	}
}
