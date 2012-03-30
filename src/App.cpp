#include "App.hpp"

#include <sstream>
#include <ctime>

App::App()
{
	generationCpt = 0;
	screened = false;
}

void App::initGenerationScenes()
{
	generationCpt++;
	int nbScenesX = 4;
	int nbScenesY = 4;
//	nbScenesX = 1;
//	nbScenesY = 1;

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

	nbAlive = nbScenesX+nbScenesY;
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
					else
						nbAlive--;
					if(it == scenes.end())
						clockParticles.restart();
				}
			}

			// drawing hud
			window->setView(window->getDefaultView());
			sf::RectangleShape bghud(sf::Vector2f(90.f, 12.f));
			bghud.setPosition(0,0);
			bghud.setFillColor(sf::Color(100,100,100));

			std::stringstream sshud;
			sshud << "Generation: " << generationCpt;
			sf::Text hudText(sshud.str());
			hudText.setCharacterSize(10);
			hudText.setColor(sf::Color::White);

			window->draw(bghud);
			window->draw(hudText);

			window->display();
			clock.restart();
		}

		// maikng snapshot
		if(generationCpt%10 == 1)
		{
			if(!screened)
			{
//				std::cout << "SMILE!" << std::endl;
				screened = true;
			}
		}
		else
		{
			screened = false;
		}

		EntityManager::getInstance()->deleteQueue();

		if(nbAlive <= 0)
		{
			// search for the most interesting
			Genome g;
			float maxScore = 0.f;
			for(unsigned int i=0; i<scenes.size(); i++)
			{
				Scene *s = scenes[i];
				if(s->getScore() > maxScore)
				{
					maxScore = s->getScore();
					g = s->getAlgGenome();
				}
			}
			// init new generation
			currentGenome = g;
			initGenerationScenes();
		}
	}
}


sf::RenderTarget* App::getRenderTarget()
{
	return this->window;
}
