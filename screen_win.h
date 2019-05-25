#pragma once
#include "cScreen.h"

class Screen_win : public cScreen {
public:
	int Run(sf::RenderWindow*, Symbol*, int*);
private:
	sf::Vector2i MouseCoordinates;
	sf::IntRect TextBox;
	sf::IntRect menu;
};
