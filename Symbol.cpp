#include "Symbol.h"

Symbol::Symbol() {
	type = EMPTY;
}

Symbol::Symbol(sf::IntRect rectangleIn, sf::Sprite Back) {
	type = EMPTY;
	rectangle = rectangleIn;
	Background = Back;
	Background.setScale(rectangle.width / 200.0, rectangle.height / 200.0);
	Background.setPosition(rectangle.left, rectangle.top);
}

sf::IntRect Symbol::GetRectangle()
{
	return rectangle;
}

Type Symbol::GetType()
{
	return type;
}

void Symbol::SetType(Type newType)
{
	type = newType;
}

sf::Sprite Symbol::GetBackground() {
	return Background;
}

void Symbol::SetBackground(sf::Sprite Texture) {
	Background = Texture;
}