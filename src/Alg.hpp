#ifndef ALG_HPP
#define ALG_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Genome.hpp"
#include "Turtle.hpp"
#include <string>
#include "Segment.hpp"
#include <Box2D/Box2D.h>
#include "Kern.hpp"

class Alg
{
public:
	Alg(b2World *physics);
	void render(sf::RenderTarget *target);

	void mutate();
	void growUp();

	void addSegment(double x1, double y1, double x2, double y2);

	bool isAlive();

private:
	int pe;
	std::string repr;
	Genome genome;
	Turtle *turtle;

	sf::Clock clock;
	float lifetime;

	Kern *kernel;

	std::vector<Segment*> segments;
	b2World *physics;
};

#endif // ALG_HPP
