#include "Screen_game.h"
#include "Draw.h"
#include "Symbol.h"
#include "GameLogic.h"
#include <iostream>



void Screen_game::SetupGrid(std::vector<std::vector<Symbol> > *SymbolMatrix, int GridDimension, sf::RenderWindow *Window, sf::Sprite TextureSprite) {
	for (int i = 0; i < GridDimension; i++) {
		for (int j = 0; j < GridDimension; j++) {
			int SCREEN_RESOLUTION = Window->getSize().y;
			sf::IntRect rectangle = sf::IntRect(i*SCREEN_RESOLUTION / GridDimension, j*SCREEN_RESOLUTION / GridDimension, SCREEN_RESOLUTION / GridDimension, SCREEN_RESOLUTION / GridDimension);
			Symbol thisSymbol = (*SymbolMatrix)[i][j];
			(*SymbolMatrix)[i][j] = Symbol::Symbol(rectangle, TextureSprite);
			if ((thisSymbol.GetType() == EMPTY) | (thisSymbol.GetType() == X) | (thisSymbol.GetType() == O)) {
				(*SymbolMatrix)[i][j].SetType(thisSymbol.GetType());
			}
		}
	}
}

int Screen_game::Run(sf::RenderWindow *Window, Symbol *winner, int *inaRow) {
	winner->SetType(X);
	int GridDimension;
	if (*inaRow == 3) {
		GridDimension = 3;
	}
	else {
		GridDimension = 30;
	}
	std::vector<std::vector<Symbol> > SymbolMatrix(GridDimension,std::vector<Symbol>(GridDimension));
	
	GameLogic gameLogic(&SymbolMatrix, winner, inaRow);

	//Initialize grid
	sf::Texture Texture;
	try {
		if (!Texture.loadFromFile("texture.png")) {
			return 0;
		}
	}
	catch (int e) {
		std::cout << "Exception Nr " << e << std::endl;
		return 0;
	}
	sf::Sprite TextureSprite;
	TextureSprite.setTexture(Texture);
	Screen_game::SetupGrid(&SymbolMatrix, GridDimension, Window, TextureSprite);
	Draw Draw(Window, &SymbolMatrix, GridDimension);
	while (Window->isOpen())
	{
		sf::Vector2i MouseCoordinates = sf::Mouse::getPosition(*Window);
		sf::Event event;
		while (Window->pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				Window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				Screen_game::SetupGrid(&SymbolMatrix, GridDimension, Window, TextureSprite);
				Draw.UpdateMatrix(&SymbolMatrix);
				Draw.ResizeUpdate();
			}
			if (event.type == sf::Event::Closed) {
				return -1;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					int winCondition = gameLogic.Update(MouseCoordinates);

					if (winCondition == 2) {
						return winCondition;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return 0;
				}
			}
		}
		Draw.DrawGameFrame(&MouseCoordinates, winner);
		Window->display();
	}
	return 0;
}
