#include <iostream>
#include <SFML/Graphics.hpp>

int main(void)
{
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(600,480,32),
																	"alg",
																	sf::Style::Close);
	while(window->IsOpened())
	{
		// close event
		sf::Event e;
		while(window->GetEvent(e)){
			if(e.Type == sf::Event::Closed)
				window->Close();
		}

		window->Clear(sf::Color(255, 255, 255));
		window->Display();
	}
	return 0;
}
