




class UI_Input_Box : public UI
{
private:

	SDL_Rect rect;

	//Border
	UI_Image* border;

	//Text
	p2SString text;
	SDL_Texture * texture;
	SDL_Color* color;
	_TTF_Font* font;

public:

	UI_Input_Box(int x, int y, bool enabled, bool draggable);

	void Update();

	void Draw();

};