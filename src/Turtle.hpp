#ifndef TURTLE_HPP
#define TURTLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Alg;

typedef struct
{
	double angle;
	double x,y;
} State;

class Turtle
{
public:
	Turtle();
	~Turtle();
	void initState(int x = 0, int y = 0);
	void rotate(bool cw = true);
	void stepLine(sf::RenderTarget *target);
	void stepLine(Alg *alg);
	void stack();
	void unstack();

	void build(const std::string &str, Alg* alg);
	void draw(const std::string &str, sf::RenderTarget *target);

private:
	std::vector<State*> states;
	double lUnit, aUnit;
};

#endif // TURTLE_HPP
