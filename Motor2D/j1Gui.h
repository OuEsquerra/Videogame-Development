#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#include "p2SString.h"
#include "p2Point.h"
#include "p2List.h"
#include "SDL/include/SDL_rect.h"
#include "j1Render.h"
#include "j1Textures.h"

#include "j1UI.h"
#include "UI_Button.h"
#include "UI_Image.h"
#include "UI_Text.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	UI_Text* CreateText(int x, int y, p2SString text);

	UI_Image* CreateImage(int x, int y,bool draggable, SDL_Rect rect, SDL_Texture* image);

	UI_Button* CreateButton(int x, int y, SDL_Rect rect, p2SString text);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	
	SDL_Texture* background;
	SDL_Texture* wow_logo;

	p2SString atlas_file_name;
	
	p2List<UI*> UI_list;
};

#endif // __j1GUI_H__