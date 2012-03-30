#include "Alg.hpp"
#include <cstdlib>
#include <iostream>
#include "LSys.hpp"
#include "const.hpp"

Alg::Alg()
{

}

Alg::Alg(b2World *physics, const Genome &genome) :
	pe(100),
	genome(genome),
	physics(physics)
{
	kernel = new Kern(physics);
	growUp();
}

void Alg::growUp()
{
	LSys ls = genome.getLSys();
	ls.iter(5);
	repr = ls.str();
//	turtle->build("F+++++++++F", this);
	turtle.build(repr, this);
	lifetime = 0;
	clock.restart();

	std::cout << "SIZE: " << repr.size() << std::endl;
}

void Alg::mutate()
{
	genome.mutateRandomScheme();
	growUp();
}

void Alg::addSegment(double x1, double y1, double x2, double y2)
{
	Segment *s = new Segment(physics, x1, y1, x2, y2);
	segments.push_back(s);
}

bool Alg::isAlive()
{
	return kernel->isAlive();
}

void Alg::render(sf::RenderTarget *target)
{
	if(isAlive())
		lifetime = clock.getElapsedTime().asSeconds();
	kernel->render(target);
	std::vector<Segment*>::iterator it;
	for(it=segments.begin(); it!=segments.end(); it++)
	{
		Segment *s = *it;
		s->render(target);
	}
}
