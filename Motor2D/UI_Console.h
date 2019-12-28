class UI_Console : public UI
{
private:

	SDL_Rect rect;

	//Text
	p2SString text;
	SDL_Texture * texture;
	SDL_Color* color;
	_TTF_Font* font;

public:

	UI_Console(int x, int y, bool enabled, bool draggable, SDL_Color* color, _TTF_Font* font, SDL_Rect rect);

	void Update();

	void Draw();

	const char* GetText() const;
};