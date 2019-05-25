#include "Draw.h"
#include <stdio.h>
#include <iostream>

Draw::Draw(sf::RenderWindow *theWindow)
{
	window = theWindow;
	LoadFiles();
	Setup();
}

Draw::Draw(sf::RenderWindow* theWindow, std::vector<std::vector < Symbol > > *Matrix, int GridDimension) {
	//	Insert thewindow to variable window
	window = theWindow;
	//	Insert windowSize to variable size
	size = (float)theWindow->getSize().x;
	//	Set rectangle color
	rectangle.setFillColor(sf::Color::Red);
	SymbolMatrix = Matrix;
	matrixSize = SymbolMatrix->size();
	Dimension = GridDimension;
	symbolWidth = (*SymbolMatrix)[0][0].GetRectangle().width;
	symbolHeight = (*SymbolMatrix)[0][0].GetRectangle().height;
	CreateSymbols();
}

void Draw::LoadFiles() {
	try {
		if (!MyFont.loadFromFile("walk.ttf")) {
			return;
		}
	}
	catch (int e) {
		std::cout << "Exception Nr " << e << std::endl;
		return;
	}
	return;
}

void Draw::CreateSymbols() {
	Ximage.loadFromFile("Xfile.png");
	Xtexture.loadFromImage(Ximage);
	Xsprite.setScale((symbolWidth / 600.0), (symbolHeight / 600.0));
	Xsprite.setTexture(Xtexture);
	Oimage.loadFromFile("Ofile2.png");
	Otexture.loadFromImage(Oimage);
	Osprite.setScale((symbolWidth / 200.0), (symbolHeight / 200.0));
	Osprite.setTexture(Otexture);
	redXImage.loadFromFile("XfileRed.png");
	redXTexture.loadFromImage(redXImage);
	redXSprite.setScale((symbolWidth / 600.0), (symbolHeight / 600.0));
	redXSprite.setTexture(redXTexture);
	redOImage.loadFromFile("Ofile2Red.png");
	redOTexture.loadFromImage(redOImage);
	redOSprite.setScale((symbolWidth / 200.0), (symbolHeight / 200.0));
	redOSprite.setTexture(redOTexture);
}


void Draw::DrawSymbols(sf::Vector2i *MouseCoordinates, Symbol *winner) {
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			float top = (float)(*SymbolMatrix)[i][j].GetRectangle().top;
			float left = (float)(*SymbolMatrix)[i][j].GetRectangle().left;
			if ((*SymbolMatrix)[i][j].GetRectangle().contains(MouseCoordinates->x, MouseCoordinates->y) && (*SymbolMatrix)[i][j].GetType() == EMPTY) {
				if (winner->GetType() == X) {
					redXSprite.setPosition(left, top);
					window->draw(redXSprite);
				}
				else if(winner->GetType() == O){
					redOSprite.setPosition(left, top);
					window->draw(redOSprite);
				}
			}
			else {
				window->draw((*SymbolMatrix)[i][j].GetBackground());
			}
			if ((*SymbolMatrix)[i][j].GetType() == X) {
				Xsprite.setPosition(left, top);
				window->draw(Xsprite);
			}
			else if ((*SymbolMatrix)[i][j].GetType() == O) {
				Osprite.setPosition(left, top);
				window->draw(Osprite);
			}
		}
	}
}



int Draw::DrawMenu(sf::Vector2i *MouseCoordinates) {
	sf::IntRect TextBox = GetTextBounds(start);
	sf::IntRect classicTextBox = GetTextBounds(classic);
	sf::IntRect fiveTextBox = GetTextBounds(fiveinrow);

	if (TextBox.contains(MouseCoordinates->x, MouseCoordinates->y)) {
		start.setFillColor(sf::Color::Red);
	}
	else if (classicTextBox.contains(MouseCoordinates->x, MouseCoordinates->y)) {
		classic.setFillColor(sf::Color::Red);
	}
	else if (fiveTextBox.contains(MouseCoordinates->x, MouseCoordinates->y)) {
		fiveinrow.setFillColor(sf::Color::Red);
	}
	else {
		start.setFillColor(sf::Color::White);
		classic.setFillColor(sf::Color::White);
		fiveinrow.setFillColor(sf::Color::White);
	}
	window->clear();
	window->draw(classic);
	window->draw(start);
	window->draw(fiveinrow);
	window->draw(Name);
	return 0;
}

void Draw::DrawGameFrame(sf::Vector2i *MouseCoordinates, Symbol *winner) {
	//Call DrawGrid method to draw the background
	Draw::DrawGrid();
	Draw::DrawSymbols(MouseCoordinates, winner);
}

//	Draw grid background
void Draw::DrawGrid() {
	window->clear(sf::Color(255,255,255));
	for (int i = 0; i < Dimension; i++) {
		for (int j = 0; j < Dimension; j++) {
			window->draw((*SymbolMatrix)[i][j].GetBackground());
		}
	}
}


void Draw::DrawWinScreen(sf::Vector2i *MouseCoordinates, Symbol *winner) {
	if (winner->GetType() == O) {
		winnerString = "Player\nO\nwins!";
	}
	else if (winner->GetType() == X) {
		winnerString = "Player\nX\nwins!";
	}
	else {
		winnerString = "No\nPlayer\nWon\n:(";
	}
	Winner.setString(winnerString);
	sf::IntRect TextBox = GetTextBounds(playagain);
	sf::IntRect menuTextBox = GetTextBounds(menu);
	if (TextBox.contains(MouseCoordinates->x, MouseCoordinates->y)) {
		playagain.setFillColor(sf::Color::Red);
	}
	else if (menuTextBox.contains(MouseCoordinates->x, MouseCoordinates->y)) {
		menu.setFillColor(sf::Color::Red);
	}
	else {
		playagain.setFillColor(sf::Color::White);
		menu.setFillColor(sf::Color::White);
	}
	window->clear();
	window->draw(playagain);
	window->draw(Winner);
	window->draw(menu);
}

sf::IntRect Draw::GetTextBounds(sf::Text text) {
	sf::IntRect rect(text.getGlobalBounds().left
		, text.getGlobalBounds().top
		, text.getGlobalBounds().width
		, text.getGlobalBounds().height
	);
	return rect;
}

void Draw::Setup() {
	//Setup Start Game font
	classic.setFont(MyFont);
	classic.setString("Classic");
	classic.setCharacterSize(50);
	classic.setFillColor(sf::Color::White);
	classic.setStyle(sf::Text::Bold);
	sf::FloatRect classicRect = classic.getGlobalBounds();
	classic.setOrigin((classicRect.left + classicRect.width) / 2.0f, (classicRect.top + classicRect.height) / 2.0f);
	classic.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);

	start.setFont(MyFont);
	start.setString("4 in a row");
	start.setCharacterSize(50);
	start.setFillColor(sf::Color::White);
	start.setStyle(sf::Text::Bold);
	sf::FloatRect startRect = start.getGlobalBounds();
	start.setOrigin((startRect.left + startRect.width) / 2.0f, (startRect.top + startRect.height) / 2.0f);
	start.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.0f / 3.0f));
	
	fiveinrow.setFont(MyFont);
	fiveinrow.setString("5 in a row");
	fiveinrow.setCharacterSize(50);
	fiveinrow.setFillColor(sf::Color::White);
	fiveinrow.setStyle(sf::Text::Bold);
	sf::FloatRect fiveinrowRect = fiveinrow.getGlobalBounds();
	fiveinrow.setOrigin((fiveinrowRect.left + fiveinrowRect.width) / 2.0f, (fiveinrowRect.top + fiveinrowRect.height) / 2.0f);
	fiveinrow.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.5f / 3.0f));
	
	//Setup game name font
	Name.setFont(MyFont);
	Name.setString("QuintQuackQoe!");
	Name.setCharacterSize(60);
	Name.setFillColor(sf::Color::White);
	Name.setStyle(sf::Text::Bold);
	sf::FloatRect NameRect = Name.getGlobalBounds();
	Name.setOrigin((NameRect.left + NameRect.width) / 2.0f, (NameRect.top + NameRect.height) / 2.0f);
	Name.setPosition(window->getSize().x / 2.0f, window->getSize().y / 10.0f);

	//Setup Start Game font
	playagain.setFont(MyFont);
	playagain.setString("Play again");
	playagain.setCharacterSize(50);
	playagain.setFillColor(sf::Color::White);
	playagain.setStyle(sf::Text::Bold);
	sf::FloatRect PlayRect = playagain.getGlobalBounds();
	playagain.setOrigin((PlayRect.left + PlayRect.width) / 2.0f, (PlayRect.top + PlayRect.height) / 2.0f);
	playagain.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.0f / 3.0f));

	//Setup Start Game font
	menu.setFont(MyFont);
	menu.setString("Start Screen");
	menu.setCharacterSize(50);
	menu.setFillColor(sf::Color::White);
	menu.setStyle(sf::Text::Bold);
	sf::FloatRect menuRect = menu.getGlobalBounds();
	menu.setOrigin((menuRect.left + menuRect.width) / 2.0f, (menuRect.top + menuRect.height) / 2.0f);
	menu.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.5f / 3.0f));

	//Setup game name font
	Winner.setFont(MyFont);
	Winner.setString("Player\nX\nwins!");
	Winner.setCharacterSize(55);
	Winner.setFillColor(sf::Color::White);
	Winner.setStyle(sf::Text::Bold);
	sf::FloatRect WinnerRect = Winner.getGlobalBounds();
	Winner.setOrigin((WinnerRect.left + WinnerRect.width) / 2.0f, (WinnerRect.top + WinnerRect.height) / 2.0f);
	Winner.setPosition(window->getSize().x / 2.0f, window->getSize().y / 5.0f);
}

void Draw::ResizeUpdate()
{
	printf("Symbolwitdh: %d", symbolWidth);
	start.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.0f / 3.0f));
	fiveinrow.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.5f / 3.0f));
	classic.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
	Name.setPosition(window->getSize().x / 2.0f, window->getSize().y / 10.0f);
	playagain.setPosition(window->getSize().x / 2.0f, window->getSize().y * (2.0f / 3.0f));
	Winner.setPosition(window->getSize().x / 2.0f, window->getSize().y / 5.0f);
	Xsprite.setScale((symbolWidth / 600.0), (symbolHeight / 600.0));
	Osprite.setScale((symbolWidth / 200.0), (symbolHeight / 200.0));
	redXSprite.setScale((symbolWidth / 600.0), (symbolHeight / 600.0));
	redOSprite.setScale((symbolWidth / 200.0), (symbolHeight / 200.0));
}

sf::Text Draw::GetStart()
{
	return start;
}

sf::Text Draw::GetPlayAgain()
{
	return playagain;
}

sf::Text Draw::GetClassic()
{
	return classic;
}

sf::Text Draw::GetfiveinRow()
{
	return fiveinrow;
}

sf::Text Draw::GetMenu()
{
	return menu;
}

void Draw::UpdateMatrix(std::vector<std::vector < Symbol > > *Matrix) {
	SymbolMatrix = Matrix;
	symbolWidth = (*SymbolMatrix)[0][0].GetRectangle().width;
	symbolHeight = (*SymbolMatrix)[0][0].GetRectangle().height;
}