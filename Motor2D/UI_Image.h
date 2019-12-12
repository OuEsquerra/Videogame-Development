

class UI_Image : public UI
{
	//Vars
	SDL_Rect rect;

	SDL_Texture* image;

	//Methods
public:

	UI_Image(int x, int y, bool draggable, SDL_Rect rect,SDL_Texture* image);

	void Update();

	void Draw();

};