#ifndef HISTORYWINDOW_HPP
#define HISTORYWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Genome.hpp"

class HistoryWindow : public sf::RenderWindow
{
public:
	HistoryWindow();
	void addGenome(const Genome &genome);
	void render();

	void manageEvents();

	void scroll(int step);

private:
	std::vector<std::string> reprs;
	sf::View view;
};

#endif // HISTORYWINDOW_HPP
