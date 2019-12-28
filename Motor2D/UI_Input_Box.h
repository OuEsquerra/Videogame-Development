




class UI_Input_Box : public UI
{
private:

	SDL_Rect rect;

	//Border
	UI_Image* border;

public:
	//Text
	p2SString text;
	SDL_Texture * texture;
	SDL_Color* color;
	_TTF_Font* font;

public:

	UI_Input_Box(int x, int y, bool enabled, bool draggable,p2SString text, SDL_Color* color, _TTF_Font* font, UI_Image* border,SDL_Rect rect);

	void Update();

	void Draw();

	const char* GetText() const;
};