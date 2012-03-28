#include "Particle.hpp"
#include "const.hpp"
#include <iostream>

Particle::Particle(b2World *physics, double x, double y) :
	Entity(physics)
{
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(x,y);

	b2CircleShape circle;
	circle.m_radius = 2.f/SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 10.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = this;

	body = physics->CreateBody(&def);
	body->CreateFixture(&fixtureDef);

	// give random initial impulse
	b2Vec2 vect(-90+(rand()%20), (rand()%60)-30);
	body->ApplyLinearImpulse(vect, body->GetWorldCenter());
}

Particle::~Particle()
{
}

void Particle::render(sf::RenderTarget *target)
{
	sf::Shape shape = sf::Shape::Circle(body->GetPosition().x,
													-body->GetPosition().y,
													2.f/SCALE, sf::Color::Blue);
	target->Draw(shape);
}
