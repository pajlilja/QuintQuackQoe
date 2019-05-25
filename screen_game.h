#pragma once
#include "cScreen.h"

class Screen_game : public cScreen {
public:
	void SetupGrid(std::vector<std::vector<Symbol> >*, int, sf::RenderWindow*, sf::Sprite);
	int Run(sf::RenderWindow*, Symbol*, int*);
private:
};