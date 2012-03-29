#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "const.hpp"
#include "Scene.hpp"
#include <SFML/System.hpp>

#include "EntityManager.hpp"

#include "Singleton.hpp"

class App : public Singleton<App>
{
	friend class Singleton<App>;
public:
	void run();
	sf::RenderTarget* getRenderTarget();

private:
	App();
	std::vector<Scene*> scenes;
	sf::RenderWindow *window;

};

#endif // APP_HPP