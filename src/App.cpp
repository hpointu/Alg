#include "App.hpp"

App::App()
{

}

void App::run()
{
	srand(time(0)); // init random

	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH,
															  W_HEIGHT,
															  32),
											"alg",
											sf::Style::Close);


	Genome copy;

	scenes.push_back(new Scene(W_WIDTH/2, W_HEIGHT/2, 0, 0));
	copy = currentGenome;
//	copy.mutateRandomScheme();
	scenes.back()->initAlg(copy);

	scenes.push_back(new Scene(W_WIDTH/2, W_HEIGHT/2, W_WIDTH/2, 0));
	copy = currentGenome;
	copy.mutateRandomScheme();
	scenes.back()->initAlg(copy);

	scenes.push_back(new Scene(W_WIDTH/2, W_HEIGHT/2, 0, W_HEIGHT/2));
	copy = currentGenome;
	copy.mutateRandomScheme();
	scenes.back()->initAlg(copy);

	scenes.push_back(new Scene(W_WIDTH/2, W_HEIGHT/2, W_WIDTH/2, W_HEIGHT/2));
	copy = currentGenome;
	copy.mutateRandomScheme();
	scenes.back()->initAlg(copy);

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
