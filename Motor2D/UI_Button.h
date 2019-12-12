
#include "j1Gui.h"


class UI_Button : public UI
{
	//Vars
public:
	SDL_Rect rect;

	SDL_Texture* button_idle;
	SDL_Texture* button_over;
	SDL_Texture* button_press;

	//Methods
public:

	UI_Button(int x, int y,bool draggable,SDL_Rect rect);

	void Update();

	void Draw();

};
