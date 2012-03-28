#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "const.hpp"
#include "Scene.hpp"
#include <SFML/System.hpp>

int main(void)
{
	srand(time(0)); // init random

	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(W_WIDTH,
																					  W_HEIGHT,
																					  32),
																	"alg",
																	sf::Style::Close);

	sf::View *view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(W_WIDTH/2,
																						W_HEIGHT/2));

	window->SetView(*view);
	view->Zoom(SCALE);

	Scene *scene = new Scene();

	sf::Clock clock, clockParticles;
	clock.Reset();
	clockParticles.Reset();
	while(window->IsOpened())
	{
		// close event
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();
		}

		if(clock.GetElapsedTime() > 1.f/60)
		{
			window->Clear(sf::Color(255, 255, 255));

			// drawing
			scene->render(window);
			window->Display();
			clock.Reset();
		}

		if(clockParticles.GetElapsedTime() > 0.1)
		{
			scene->throwParticle(10);
			clockParticles.Reset();
		}
	}
	return 0;
}
