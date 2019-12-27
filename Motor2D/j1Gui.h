#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1App.h"
#include "j1Module.h"

#include "p2SString.h"
#include "p2Point.h"
#include "p2List.h"
#include "SDL/include/SDL_rect.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Audio.h"

#include "j1UI.h"
#include "UI_Button.h"
#include "UI_Image.h"
#include "UI_Text.h"

#include "UI_Window.h"

//class UI_Window;

#define CURSOR_WIDTH 2


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	virtual ~j1Gui();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	UI_Text* CreateText(int x, int y, bool active, bool draggable, p2SString text, SDL_Color* color, const char* path,int size);

	UI_Image* CreateImage(int x, int y, bool active,bool draggable, SDL_Rect rect, SDL_Texture* image);

	UI_Button* CreateButton(int x, int y, bool active, bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect* default_rect, SDL_Rect* hover_rect, SDL_Rect* press_rect, SDL_Texture* image,SDL_Rect rect, int x_offset, int y_offset);

	UI_Window* CreateUiWindow(int x, int y, int enabled = false);
private:
	


	p2SString atlas_file_name;
	
	p2List<UI*> UI_list;

public:
	p2List<UI_Window*> Windows_list;
	int click_audio;
};

#endif // __j1GUI_H__