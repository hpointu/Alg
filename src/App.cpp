#include "App.hpp"

App::App()
{

}

void App::initGenerationScenes()
{
	int nbScenesX = 4;
	int nbScenesY = 3;
	Genome copy = currentGenome;

	scenes.clear();

	for(int j=0; j<nbScenesY; j++)
	{
		for(int i=0; i<nbScenesX; i++)
		{
			scenes.push_back(new Scene(W_WIDTH/nbScenesX,
												W_HEIGHT/nbScenesY,
												i*(W_WIDTH/nbScenesX),
												j*(W_HEIGHT/nbScenesY))
								  );
			scenes.back()->initAlg(copy);
			copy = currentGenome;
			copy.mutateRandomScheme();
		}
	}
}

void App::run()
{
	srand(time(0)); // init random

	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH,
															  W_HEIGHT,
															  32),
											"alg",
											sf::Style::Close);



	initGenerationScenes();

//	scenes.push_back(new Scene(W_WIDTH, W_HEIGHT, 0, 0));

	sf::Clock clock, clockParticles;
	clock.restart();
	clockParticles.restart();
	while(window->isOpen())
	{
		// close event
		sf::Event e;
		while(window->pollEvent(e)){
			if(e.type == sf::Event::Closed)
				window->close();
		}

		if(clock.getElapsedTime().asSeconds() > 1.f/60)
		{
			window->clear(sf::Color(255, 255, 255));

			// drawing
			std::vector<Scene*>::iterator it;
			for(it=scenes.begin(); it!=scenes.end(); it++)
			{
				Scene *scene = *it;
				scene->render(window);
				if(clockParticles.getElapsedTime().asSeconds() > 0.1)
				{
					if(scene->isRunning())
						scene->throwParticle(10);
					if(it == scenes.end())
						clockParticles.restart();
				}
			}
			window->display();
			clock.restart();
		}

		EntityManager::getInstance()->deleteQueue();
	}
}


sf::RenderTarget* App::getRenderTarget()
{
	return this->window;
}
