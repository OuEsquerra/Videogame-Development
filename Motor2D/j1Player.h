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

struct Player {
	float acceleration;

	float speedX;

	float maxSpeed;

	float floor = 400.0f;

	int boxW = 40;
	int boxH = 70;

	SDL_Rect playerBox;

	p2Point<float> positionP1;

	PlayerState playerState;



};

class j1Player : public j1Module {
public://methods

	j1Player();

	// Destructor
	virtual ~j1Player();

	bool Init();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool cleanUp();

private:

	
public://variables

	

	

private:

	float frames = 0;

	bool runFrames = false;

	float startFrame = 0;

	Player player;

	//j1Input playerInput;
};


#endif
