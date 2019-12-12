


class UI_Text : public UI
{
	//Vars
	p2SString text;

	//Methods
public:

	UI_Text(int x, int y, bool draggable, SDL_Rect rect);

	void Update();

	void Draw();

};