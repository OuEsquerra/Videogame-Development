
class UI_Slider : public UI
{
public:
	//Vars
	SDL_Rect rect;

	UI_Image* slider;
	UI_Image* bar;

	//Methods
public:

	UI_Slider(int x, int y, bool active, bool draggable, SDL_Rect rect, SDL_Texture* image = nullptr);

	void Update();

	void Draw();

};