#include "Screen_win.h"
#include "Draw.h"

int Screen_win::Run(sf::RenderWindow *Window, Symbol *winner, int *inaRow) {
	Draw Draw(Window);
	while (Window->isOpen())
	{
		sf::Event event;
		while (Window->pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				Window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				Draw.ResizeUpdate();
			}
			if (event.type == sf::Event::Closed)
				return -1;

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					MouseCoordinates = sf::Mouse::getPosition(*Window);
					TextBox = Draw.GetTextBounds(Draw.GetPlayAgain());
					menu = Draw.GetTextBounds(Draw.GetMenu());
					if (TextBox.contains(MouseCoordinates.x, MouseCoordinates.y)) {
						return 1;
					}
					if (menu.contains(MouseCoordinates.x, MouseCoordinates.y)) {
						return 0;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return 0;
				}
			}
		}
		MouseCoordinates = sf::Mouse::getPosition(*Window);
		Draw.DrawWinScreen(&MouseCoordinates, winner);
		Window->display();
	}
	return -1;
}