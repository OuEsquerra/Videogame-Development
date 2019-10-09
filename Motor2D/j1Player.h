#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"

class j1Player : public j1Module {
public://methods
	bool Init();

	bool Awake(pugi::xml_node config);

	bool Start();

	bool preUpdate();

	bool Update();

	bool postUpdate();

	bool cleanUp();

private:

	
public://variables

	

	

private:

	SDL_Rect playerBox;
	iPoint positionP1;
	
	

};


#endif
