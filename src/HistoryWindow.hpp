#ifndef HISTORYWINDOW_HPP
#define HISTORYWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Turtle.hpp"
#include "Genome.hpp"

class HistoryWindow : public sf::RenderWindow
{
public:
	struct Infos
	{
		std::string repr;
		int generation;
	};

	HistoryWindow(sf::ContextSettings settings);
	void addGenome(const Genome &genome, int generation);
	void render();
	void open();

	void manageEvents();

	void scroll(int step);

private:
	std::vector<HistoryWindow::Infos> reprs;
	sf::View view;
	Turtle turtle;
	int vstep;

	void drawAlg(sf::RenderTarget *target, int y, unsigned int i);
};

#endif // HISTORYWINDOW_HPP
