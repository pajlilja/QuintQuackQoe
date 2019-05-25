#pragma once
#include "cScreen.h"

class Screen_menu : public cScreen {
public:
	int Run(sf::RenderWindow*, Symbol*, int*);
private:
	sf::Vector2i MouseCoordinates;
	sf::IntRect StartTextBox;
	sf::IntRect ClassicTextBox;
	sf::IntRect FiveTextBox;
};