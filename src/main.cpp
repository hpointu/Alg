#include "App.hpp"

int main(void)
{
	App::getInstance()->run();
	App::kill();
	return 0;
}
