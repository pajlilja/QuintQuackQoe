#pragma once
#include <SFML/Graphics.hpp>
#include "Symbol.h"

class Draw {
public:
	Draw(sf::RenderWindow*);
	Draw(sf::RenderWindow*, std::vector<std::vector < Symbol > >*, int);
	void Draw::LoadFiles();
	void CreateSymbols();
	void DrawSymbols(sf::Vector2i*, Symbol*);
	int Draw::DrawMenu(sf::Vector2i*);
	void DrawGameFrame(sf::Vector2i*, Symbol*);
	void DrawGrid();
	void Draw::DrawWinScreen(sf::Vector2i*, Symbol*);
	sf::IntRect Draw::GetTextBounds(sf::Text);
	void Draw::Setup();
	void ResizeUpdate();
	sf::Text GetStart();
	sf::Text GetPlayAgain();
	sf::Text GetClassic();
	sf::Text GetfiveinRow();
	sf::Text GetMenu();
	void UpdateMatrix(std::vector<std::vector < Symbol > > *);
private:
	int symbolHeight;
	int symbolWidth;
	int matrixSize;
	int Dimension;
	float size;
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;
	sf::Image redOImage;
	sf::Texture redOTexture;
	sf::Sprite redOSprite;
	sf::Image redXImage;
	sf::Texture redXTexture;
	sf::Sprite redXSprite;
	sf::Texture Xtexture;
	sf::Image Ximage;
	sf::Sprite Xsprite;
	sf::Texture Otexture;
	sf::Image Oimage;
	sf::Sprite Osprite;
	std::vector<std::vector < Symbol > > *SymbolMatrix;
	sf::Font MyFont;
	std::string winnerString;
	sf::Text start;
	sf::Text classic;
	sf::Text fiveinrow;
	sf::Text playagain;
	sf::Text Name;
	sf::Text Winner;
	sf::Text menu;
};