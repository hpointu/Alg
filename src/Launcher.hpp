#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

class Launcher
{
public:
	enum Side
	{
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};

	struct Params
	{
		float x;
		float y;
		float ix;
		float iy;
		float baseAngle;
		float realAngle;
		Launcher::Side side;
	};


	Launcher(float width, float height);
	Launcher::Params generateRandomParams();
	Launcher::Params getCurrentParams(){ return params; }

private:
	Launcher::Params params;
	float width, height;
};

#endif // LAUNCHER_HPP
