#include "Alg.hpp"
#include <cstdlib>
#include <iostream>
#include "LSys.hpp"

Alg::Alg() :
	pe(100)
{
	kernelShape = sf::Shape::Circle(1024/2, 768/2, 4, sf::Color(180, 0, 0, 140));

	growUp();
}

void Alg::growUp()
{
	LSys ls = genome.getLSys();
	ls.iter(5);
	this->repr = ls.str();

	std::cout << "SIZE: " << repr.size() << std::endl;
}

void Alg::mutate()
{
	genome.mutateRandomScheme();
	growUp();
}

void Alg::draw(sf::RenderTarget *target)
{
	target->Draw(this->kernelShape);

	turtle.drawString(repr, target);
}
