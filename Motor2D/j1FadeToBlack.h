#ifndef __J1FADETOBLACK_H__
#define __J1FADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack();
	~j1FadeToBlack();

	bool Start();
	bool Update(float dt);
	bool FadeToBlack(const char* mapname,  bool reset_player = true, float time = 0.5f);
	bool SwitchMap(const char* mapname);

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

public:

	bool playerReset = true;

private:
	
	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	
	const char* map_name;

};

#endif //__MODULEFADETOBLACK_H__