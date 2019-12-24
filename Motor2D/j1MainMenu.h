#include "j1Module.h"
#include "SDL/include/SDL_rect.h"
class UI_Image;
struct SDL_Texture;
class UI_Text;
class UI_Button;


class j1MainMenu : public j1Module
{
public:

	j1MainMenu();

	~j1MainMenu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

public:
	SDL_Texture* debug_tex;

	UI_Button* new_button;

	UI_Button* button2;

	UI_Image* wowLogo;

	SDL_Rect button_rect = { 0, 0, 244, 56 };

	SDL_Rect default_rect = { 0, 0, 244, 56 };
	SDL_Rect hover_rect = { 0, 60, 244, 56 };
	SDL_Rect press_rect = { 0, 120, 244, 56 };

	UI_Text* Bootleg;
	SDL_Color bootleg_color = { (0),(0),(0),(255) };

	SDL_Texture* button_idle;
	SDL_Texture* button_over;
	SDL_Texture* button_press;

};
