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
#include "Genome.hpp"
#include "Alg.hpp"
#include "HistoryWindow.hpp"

class App : public Singleton<App>
{
	friend class Singleton<App>;
public:
	void run();
	sf::RenderTarget* getRenderTarget();
	void initGenerationScenes();

private:
	App();
	std::vector<Scene*> scenes;
	int nbAlive;
	sf::RenderWindow *window;
	HistoryWindow *history;
	Genome currentGenome;

	int generationCpt;
	bool screened;

};

#endif // APP_HPP
