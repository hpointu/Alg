#ifndef ALG_HPP
#define ALG_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Genome.hpp"
#include "Turtle.hpp"
#include <string>

class Alg
{
public:
	Alg();
	void draw(sf::RenderTarget *target);

	void mutate();
	void growUp();

private:
	int pe;
	std::string repr;
	Genome genome;
	sf::Shape kernelShape;
	Turtle turtle;
};

#endif // ALG_HPP
