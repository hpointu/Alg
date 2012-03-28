#ifndef SCENE_HPP
#define SCENE_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Alg.hpp"
#include "Particle.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	void render(sf::RenderTarget *target);

	void throwParticle(int nb=1);

	bool isRunning();

private:
	Alg *alg;
	b2World *physics;
	std::vector<Particle*> particles;
	bool running;
};

#endif // SCENE_HPP
