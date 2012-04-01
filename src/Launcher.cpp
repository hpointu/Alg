#include "Launcher.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

Launcher::Launcher(float width, float height) :
	width(width),
	height(height)
{
	float angle = rand()%360;
	params.baseAngle = angle;

	std::cout << angle << std::endl;
}

Launcher::Params Launcher::generateRandomParams()
{
	double beta = ::atan(height/width); // angle de diagonale de scene

	double alpha = params.baseAngle * M_PI/180;

	float modAngle = (rand()%40)-25;
	params.realAngle = params.baseAngle+modAngle; // angle de lancement reel
	double alphaReal = params.realAngle * M_PI/180;

	// calcul coords
	if(alpha <= beta || alpha > (2*M_PI)-beta)
	{
		params.side = RIGHT;
		params.x = -width/2;
		params.y = -::sin(alpha) * width/2;

		params.y += (rand()%(int)height) - height/2;
	}
	else if(alpha <= M_PI-beta && alpha > beta)
	{
		params.side = TOP;
		params.x = -::cos(alpha) * height/2;
		params.y = -height/2;

		params.x += (rand()%(int)width) - width/2;
	}
	else if(alpha <= M_PI+beta && alpha > M_PI-beta)
	{
		params.side = LEFT;
		params.x = width/2;
		params.y = -::sin(alpha) * width/2;

		params.y += (rand()%(int)height) - height/2;
	}
	else if(alpha <= (2*M_PI)-beta && alpha > M_PI+beta)
	{
		params.side = BOTTOM;
		params.x = -::cos(alpha) * height/2;
		params.y = height/2;

		params.x += (rand()%(int)width) - width/2;
	}



	int power = 180;
	params.ix = ::cos(alphaReal)*power;
	params.iy = ::sin(alphaReal)*power;

	return Params(params);
}
