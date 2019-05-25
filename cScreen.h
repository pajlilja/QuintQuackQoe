#pragma once
#include <SFML/Graphics.hpp>
#include "Symbol.h"

class cScreen
{
public:
	virtual int Run(sf::RenderWindow *App, Symbol *winner, int *inaRow) = 0;
};