#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

class UI_Image;
struct SDL_Texture;
class UI_Text;
class UI_Button;
class UI;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	//HUD data
	int coin_score;
	int score;
	int time;
	int lives;

private:

	SDL_Texture* debug_tex;

	//Default buttons
	UI_Button* button;

	SDL_Rect button_rect = { 0, 0, 244, 56 };

	SDL_Rect default_rect = { 0, 0, 244, 56 };
	SDL_Rect hover_rect = { 0, 60, 244, 56 };
	SDL_Rect press_rect = { 0, 120, 244, 56 };

	UI_Text* Bootleg;
	SDL_Color bootleg_color = {(75),(0),(130),(255)};

	//HUD
	SDL_Texture* UI_HUD_Left_Tex;
	SDL_Texture* UI_HUD_Right_Tex;

	UI_Image* UI_HUD_Left;
	UI_Image* UI_HUD_Right;

	UI_Image* UI_Life_Segments[3];

	p2List<UI*> HUD_elements;
};

#endif //__j1SCENE_H__