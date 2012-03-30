#include "HistoryWindow.hpp"
#include "const.hpp"
#include "LSys.hpp"
#include "Turtle.hpp"

HistoryWindow::HistoryWindow() :
	sf::RenderWindow(sf::VideoMode(HIST_WIDTH,
											 HIST_HEIGHT,
											 32),
						  "History",
						  sf::Style::Titlebar)
{
	view = sf::View(sf::Vector2f(0, HIST_HEIGHT/2), sf::Vector2f(HIST_WIDTH/2,
																					 HIST_HEIGHT/2));

	view.zoom(2.f);

}

void HistoryWindow::addGenome(const Genome &genome)
{
	LSys ls = genome.getLSys();
	ls.iter(5);
	reprs.push_back(ls.str());
}

void HistoryWindow::manageEvents()
{
	sf::Event event;
	while(this->pollEvent(event)){
		if(event.type == sf::Event::MouseWheelMoved)
		{
			int delta = event.mouseWheel.delta;
			int step = 50;
			if(delta>0)
				scroll(-step);
			else
				scroll(step);
		}
	}
}

void HistoryWindow::scroll(int step)
{
	if(step>0) // scroll down
	{
		view.move(0, step);
	}
	else  // scroll up
	{
		if(view.getCenter().y > HIST_HEIGHT/2)
			view.move(0, step);
	}
}

void HistoryWindow::render()
{
	this->setView(view);
	this->clear(sf::Color(255, 255, 255));

	Turtle t;

	int vstep = 200;
	for(unsigned int i=0; i<reprs.size(); i++)
	{
		float y = (vstep/2.f)+i*vstep;
		t.initState(0, y+(vstep/6));
		t.draw(reprs[i], this);

		if(i<reprs.size()-1)
		{
			// draw arrow

			sf::ConvexShape polygon(7);
			polygon.setPoint(0, sf::Vector2f(-6.f, -8.f));
			polygon.setPoint(1, sf::Vector2f(6.f, -8.f));
			polygon.setPoint(2, sf::Vector2f(6.f, 8.f));
			polygon.setPoint(3, sf::Vector2f(12.f, 8.f));
			polygon.setPoint(4, sf::Vector2f(0, 17.f));
			polygon.setPoint(5, sf::Vector2f(-12.f, 8.f));
			polygon.setPoint(6, sf::Vector2f(-6.f, 8.f));
			polygon.setFillColor(sf::Color(150, 150, 150));
			polygon.setPosition(0, y+vstep/2.f);
			this->draw(polygon);
		}

		// cadre
		sf::RectangleShape rect(sf::Vector2f(HIST_WIDTH, vstep));
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(1.f);
		rect.setFillColor(sf::Color::Transparent);
		rect.setPosition(-HIST_WIDTH/2.f, y-(vstep/2.f));
		this->draw(rect);

	}

	this->display();
}
