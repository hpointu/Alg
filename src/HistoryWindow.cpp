#include "HistoryWindow.hpp"
#include "const.hpp"
#include "LSys.hpp"
#include <sstream>
#include "App.hpp"
#include "Launcher.hpp"
#include <ctime>

HistoryWindow::HistoryWindow(sf::ContextSettings settings) :
	sf::RenderWindow(sf::VideoMode(HIST_WIDTH,
											 HIST_HEIGHT,
											 32),
						  "History",
						  sf::Style::Close,
						  settings)
{
	view = sf::View(sf::Vector2f(0, HIST_HEIGHT/2.f), sf::Vector2f(HIST_WIDTH/2.f,
																						HIST_HEIGHT/2.f));
	view.zoom(2.f);
	vstep = 250;
}

void HistoryWindow::addGenome(const Genome &genome, int generation)
{
	LSys ls = genome.getLSys();
	ls.iter(NB_RECURSE);

	HistoryWindow::Infos infos;
	infos.repr = ls.str();
	infos.generation = generation;
	reprs.push_back(infos);

	// export to image
	sf::RenderTexture rt;
	rt.create(HIST_WIDTH, vstep);
	sf::View v(sf::Vector2f(0, vstep/2.f), sf::Vector2f(HIST_WIDTH/2.f,
																			 vstep/2.f));
	v.zoom(2.f);
	rt.setView(v);
	rt.clear(sf::Color::White);

	drawAlg(&rt, vstep/2.f, reprs.size()-1);

	rt.display();
	sf::Texture tex = rt.getTexture();
	sf::Image img = tex.copyToImage();

	std::stringstream filename;
	filename << "history/generation-";
	filename << generation << ".png";
	img.saveToFile(filename.str());

}

void HistoryWindow::manageEvents()
{
	sf::Event event;
	while(this->pollEvent(event)){
		// mouse scroll
		if(event.type == sf::Event::MouseWheelMoved)
		{
			int delta = event.mouseWheel.delta;
			int step = 50;
			if(delta>0)
				scroll(-step);
			else
				scroll(step);
		}
		// keys
		else if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::H)
			{
				this->close();
			}
			else if(event.key.code == sf::Keyboard::P)
			{
				sf::Image img = this->capture();
				img.saveToFile("capture.png");
			}
		}
		else if(event.type == sf::Event::Closed)
			this->close();
	}
}

void HistoryWindow::open()
{
	this->create(sf::VideoMode(HIST_WIDTH,
										HIST_HEIGHT,
										32),
					 "History",
					 sf::Style::Close);
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

	for(unsigned int i=0; i<reprs.size(); i++)
	{
		float y = (vstep/2.f)+i*vstep;
		drawAlg(this, y, i);
	}

	this->display();
}

void HistoryWindow::drawAlg(sf::RenderTarget *target, int y, unsigned int i)
{
	// kernel
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Color col =  sf::Color(100, 100, 100);
	sf::CircleShape shape;
	shape.setRadius((float)KERNEL_RADIUS);
	shape.setPosition(-(float)KERNEL_RADIUS,y-(float)KERNEL_RADIUS+(vstep/6));
	shape.setFillColor(col);
	target->draw(shape);

	// particles direction
	Launcher::Params params = App::getInstance()->getLauncher()->getCurrentParams();
	sf::ConvexShape arrow(3);
	arrow.setPoint(0, sf::Vector2f(-5.f, -15.f));
	arrow.setPoint(1, sf::Vector2f(5.f, -15.f));
	arrow.setPoint(2, sf::Vector2f(0.f, 15.f));
	arrow.setFillColor(sf::Color(0, 0, 150, 160));
	arrow.setPosition(HIST_WIDTH/2-30, y+(vstep/2.f)-30);
	arrow.rotate(params.baseAngle-90);
	target->draw(arrow);

	// segments
	turtle.initState(0, y+(vstep/6));
	turtle.draw(reprs[i].repr, target);

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
		target->draw(polygon);
	}

	// cadre
	sf::RectangleShape rect(sf::Vector2f(HIST_WIDTH, vstep));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1.f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(-HIST_WIDTH/2.f, y-(vstep/2.f));
	target->draw(rect);

	sf::RectangleShape infosBg(sf::Vector2f(100, 15));
	infosBg.setFillColor(sf::Color(100,100,100));
	infosBg.setPosition(-HIST_WIDTH/2.f, y-(vstep/2.f));
	std::stringstream sshud;
	sshud << "Generation: " << reprs[i].generation;
	sf::Text genText(sshud.str(), font);
	genText.setPosition(-HIST_WIDTH/2.f +3, y-(vstep/2.f));
	genText.setCharacterSize(10);
	genText.setColor(sf::Color::White);
	sf::Text sizeText = genText;
	sshud.str("");
	sshud << "size: " << reprs[i].repr.size();
	sizeText.setString(sshud.str());
	sizeText.setColor(sf::Color::Black);
	sizeText.setPosition(-HIST_WIDTH/2.f + 3, y-(vstep/2.f)+15);
	target->draw(infosBg);
	target->draw(genText);
	target->draw(sizeText);
}
