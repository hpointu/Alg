#include "App.hpp"

#include <sstream>
#include <ctime>

App::App()
{
	srand(time(0)); // init random

	generationCpt = 0;
	screened = false;

	nbScenesX = 3;
	nbScenesY = 4;

	launcher = new Launcher(W_WIDTH/nbScenesX, W_HEIGHT/nbScenesY);
}

App::~App()
{
	scenes.clear();
	delete window;
	delete history;
	delete launcher;
}

Launcher::Params App::getParticleParams()
{
	return launcher->generateRandomParams();
}

void App::initGenerationScenes()
{
	generationCpt++;

	Genome copy = currentGenome;

	std::vector<Scene*>::iterator it;
	for(it=scenes.begin(); it!=scenes.end(); it++)
	{
		delete *it;
	}

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

	nbAlive = nbScenesX*nbScenesY;

	if(generationCpt%10==1)
		history->addGenome(currentGenome, generationCpt);
}

void App::run()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 3;

	window = new sf::RenderWindow(sf::VideoMode(W_WIDTH,
															  W_HEIGHT,
															  32),
											"Alg",
											sf::Style::Close, settings);

	history = new HistoryWindow(settings);



	initGenerationScenes();

//	scenes.push_back(new Scene(W_WIDTH, W_HEIGHT, 0, 0));

	sf::Clock clock, clockParticles;
	clock.restart();
	clockParticles.restart();
	while(window->isOpen() && generationCpt < 4000)
	{
		// close event
		sf::Event e;
		while(window->pollEvent(e)){
			if(e.type == sf::Event::Closed)
				window->close();
			// keys
			else if(e.type == sf::Event::KeyPressed)
			{
				if(e.key.code == sf::Keyboard::H)
				{
					if(history->isOpen())
						history->close();
					else
						history->open();
				}
			}
		}

		history->manageEvents();

		if(clock.getElapsedTime().asSeconds() > 1.f/60)
		{
			window->clear(sf::Color(255, 255, 255));
			// drawing
			std::vector<Scene*>::iterator it;
			nbAlive = 0;
			for(it=scenes.begin(); it!=scenes.end(); it++)
			{
				Scene *scene = *it;
				scene->render(window);
				if(clockParticles.getElapsedTime().asSeconds() > 0.1)
				{
					if(scene->isRunning())
					{
						scene->throwParticle(8);
						nbAlive++;
					}
					if(it == scenes.end())
						clockParticles.restart();
				}
			}

			// drawing hud
			window->setView(window->getDefaultView());
			sf::RectangleShape bghud(sf::Vector2f(90.f, 12.f));
			bghud.setPosition(0,0);
			bghud.setFillColor(sf::Color(100,100,100));

			sf::Font font;
			font.loadFromFile("arial.ttf");
			std::stringstream sshud;
			sshud << "Generation: " << generationCpt;
			sf::Text hudText(sf::String(sshud.str()), font);
			hudText.setCharacterSize(10);
			hudText.setColor(sf::Color::White);

			window->draw(bghud);
			window->draw(hudText);

			window->display();

			history->render();

			clock.restart();
		}

		EntityManager::getInstance()->deleteQueue();


		if(nbAlive <= 1)
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
