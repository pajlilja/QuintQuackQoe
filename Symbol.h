#pragma once
#include <SFML/Graphics.hpp>

enum Type {
	EMPTY,
	X,
	O
};

class Symbol {
public:
	Symbol();
	Symbol(sf::IntRect, sf::Sprite);
	sf::IntRect GetRectangle();
	Type GetType();
	void SetType(Type);
	sf::Sprite GetBackground();
	void SetBackground(sf::Sprite);

private:
	sf::IntRect rectangle;
	Type type;
	sf::Sprite Background;
};