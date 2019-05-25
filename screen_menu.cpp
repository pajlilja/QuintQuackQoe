#include "Screen_menu.h"
#include "Draw.h"

int Screen_menu::Run(sf::RenderWindow *Window, Symbol *winner, int *inaRow) {
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
					StartTextBox = Draw.GetTextBounds(Draw.GetStart());
					ClassicTextBox = Draw.GetTextBounds(Draw.GetClassic());
					FiveTextBox = Draw.GetTextBounds(Draw.GetfiveinRow());
					if (ClassicTextBox.contains(MouseCoordinates.x, MouseCoordinates.y)) {
						*inaRow = 3;
						return 1;
					}
					if (StartTextBox.contains(MouseCoordinates.x, MouseCoordinates.y)) {
						*inaRow = 4;
						return 1;
					}
					if (FiveTextBox.contains(MouseCoordinates.x, MouseCoordinates.y)) {
						*inaRow = 5;
						return 1;
					}
				}
			}
		}
		MouseCoordinates = sf::Mouse::getPosition(*Window);
 		Draw.DrawMenu(&MouseCoordinates);
		Window->display();
	}
	return -1;
}