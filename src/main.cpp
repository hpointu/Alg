#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Alg.hpp"

int main(void)
{
	srand(time(0)); // init random

	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1024,768,32),
																	"alg",
																	sf::Style::Close);
	Alg *alg = new Alg();

	while(window->IsOpened())
	{
		// close event
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();
			else if(e.Type == sf::Event::MouseButtonPressed &&
					  e.MouseButton.Button == sf::Mouse::Left)
			{
				alg->mutate();
			}
		}

		window->Clear(sf::Color(255, 255, 255));

		// drawing
		alg->draw(window);
		window->Display();
//		alg->mutate();
//		alg->growUp();
	}
	return 0;
}
