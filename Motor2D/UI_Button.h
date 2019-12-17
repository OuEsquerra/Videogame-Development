
#include "j1Gui.h"


class UI_Text;
class UI_Image;


class UI_Button : public UI
{
	//Vars
public:
	SDL_Rect rect;

	UI_Text* ui_text;

	UI_Image* ui_image;
	SDL_Texture* button_idle;
	SDL_Texture* button_over;
	SDL_Texture* button_press;


	//Methods
public:


	UI_Button(int x, int y,bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect rect, SDL_Texture* image = nullptr);

	void Update();

	void Draw();

};
