#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entity.hpp"

class Particle : public Entity
{
public:
	Particle(b2World *physics, double x, double y, double ix, double iy);
	~Particle();

	void render(sf::RenderTarget *target);

};

#endif // PARTICLE_HPP
