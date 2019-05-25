#include "Screen.h"
#include "Symbol.h"

int main()
{
	//Setup Screen resolution and window
	const int SCREEN_RESOLUTION = sf::VideoMode::getDesktopMode().height / 2;
	sf::RenderWindow Window(sf::VideoMode(SCREEN_RESOLUTION, SCREEN_RESOLUTION), "QuintQuackQoe!");
	
	//Setup Winner variable
	Symbol winner;
	int inaRow = 5;
	
	//Setup Vector for different stages
	std::vector<cScreen*> Screens;
	Screen_menu s0;
	Screens.push_back(&s0);
	Screen_game s1;
	Screens.push_back(&s1);
	Screen_win s2;
	Screens.push_back(&s2);

	//Start screen
	int screen = 0;

	//Gameloop for handeling current stage
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(&Window, &winner, &inaRow);
	}

	//Return 0 if successful exit
	return EXIT_SUCCESS;
}