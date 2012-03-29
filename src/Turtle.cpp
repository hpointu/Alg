#include "Turtle.hpp"
#include <cmath>
#include "const.hpp"
#include "Alg.hpp"

Turtle::Turtle() :
	lUnit(5.f), aUnit(10.f)
{
}

void Turtle::initState()
{
	// init state
	State *s = new State();
	s->angle = 270.f;
	s->x = 0;
	s->y = 0;
	this->states.push_back(s);
}

void Turtle::stack()
{
	State *s = new State(*states.back());
	states.push_back(s);
}

void Turtle::unstack()
{
	states.pop_back();
}

void Turtle::rotate(bool cw)
{
	states.back()->angle += cw ? aUnit : -aUnit;
}

void Turtle::stepLine(sf::RenderTarget *target)
{
//	State *currentState = states.back();
//	double x2 = currentState->x;
//	double y2 = currentState->y;
//	double radAngle = currentState->angle*M_PI/180;
//	x2 += ::cos(radAngle)*lUnit;
//	y2 += ::sin(radAngle)*lUnit;

//	sf::Shape line = sf::Shape::Line(currentState->x/SCALE, currentState->y/SCALE,
//												x2/SCALE, y2/SCALE, 1.f/SCALE, sf::Color::Black);

//	// update state
//	currentState->x = x2;
//	currentState->y = y2;

//	target->Draw(line);
}

void Turtle::stepLine(Alg *alg)
{
	State *currentState = states.back();
	double x2 = currentState->x;
	double y2 = currentState->y;
	double radAngle = currentState->angle*M_PI/180;
	x2 += ::cos(radAngle)*lUnit;
	y2 += ::sin(radAngle)*lUnit;

	alg->addSegment(currentState->x, currentState->y,
						 x2, y2);

	// update state
	currentState->x = x2;
	currentState->y = y2;

}

void Turtle::build(const std::string &str, Alg* alg)
{
	unsigned int i;
	char c;

	initState();
	for(i=0; i<str.size(); i++)
	{
		c = str[i];
		switch(c)
		{
		// allowed letters
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			stepLine(alg);
			break;

		// other symbols
		case '+':
			rotate(true);
			break;
		case '-':
			rotate(false);
			break;
		case '[':
			stack();
			break;
		case ']':
			unstack();
			break;

		// ignore other
		default:
			break;
		}
	}
}
