#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

class UI_Image;
struct SDL_Texture;
class UI_Text;

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

private:
	SDL_Texture* debug_tex;

	UI_Image* wowLogo;

	UI_Text* Bootleg;
	SDL_Color bootleg_color = { (255),(255),(1),(1) };

public:
	
};

#endif // __j1SCENE_H__