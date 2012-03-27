#ifndef TURTLE_HPP
#define TURTLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

typedef struct
{
	double angle;
	double x,y;
} State;

class Turtle
{
public:
	Turtle();
	void initState();
	void rotate(bool cw = true);
	void stepLine(sf::RenderTarget *target);
	void stack();
	void unstack();

	void drawString(const std::string &str,
						 sf::RenderTarget *target);

private:
	std::vector<State*> states;
	double lUnit, aUnit;
};

#endif // TURTLE_HPP
