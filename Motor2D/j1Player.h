#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"

enum PlayerState {
	idle,
	runningRight,
	runningLeft,
	jumping,

};


class j1Player : public j1Module {
public://methods

	j1Player();

	// Destructor
	virtual ~j1Player();

	bool Init();

	bool Awake(pugi::xml_node config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool cleanUp();

private:

	
public://variables

	

	

private:

	float floor = 500.0f;

	int boxW = 50;
	int boxH = 100;

	float playerSpeed = 5;

	int accelerationFrames = 0;


	SDL_Rect playerBox;
	p2Point<float> positionP1;
	
	PlayerState playerState;

	//j1Input playerInput;
};


#endif
