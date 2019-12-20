
#include "j1Gui.h"


class UI_Text;
class UI_Image;


class UI_Button : public UI
{
	//Vars
public:
	SDL_Rect rect;

	//Text
	p2SString text;
	SDL_Texture * text_texture;
	SDL_Color* color;
	_TTF_Font* font;

	//Image
	SDL_Texture* image_texture;
	SDL_Rect* image_rect;

	//Methods
public:


	UI_Button(int x, int y, bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect image_rect, SDL_Texture* image);

	void Update();

	void Draw();

};
