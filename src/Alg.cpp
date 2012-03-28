#include "Alg.hpp"
#include <cstdlib>
#include <iostream>
#include "LSys.hpp"
#include "const.hpp"

Alg::Alg(b2World *physics) :
	pe(100),
	physics(physics)
{
	turtle = new Turtle();
	kernelShape = sf::Shape::Circle(0, 0,
											  10.f/SCALE, sf::Color(180, 0, 0, 200));

	growUp();
}

void Alg::growUp()
{
	LSys ls = genome.getLSys();
	ls.iter(5);
	repr = ls.str();
	turtle->build(repr, this);

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

void Alg::render(sf::RenderTarget *target)
{
	target->Draw(this->kernelShape);
	std::vector<Segment*>::iterator it;
	for(it=segments.begin(); it!=segments.end(); it++)
	{
		Segment *s = *it;
		// clean and render :
		if(!s->dead)
		{
			s->render(target);
		}
		else
		{
			s->deleteMe();
			segments.erase(it);
		}
	}
}
