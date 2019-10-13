#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"


struct Collider;

enum PlayerState {
	idle,
	runningRight,
	runningLeft,
	jumping,
	falling
};

struct Player {
	
	p2Point<float> acceleration;

	p2Point<float> speed;
	p2Point<float> maxSpeed;

	p2SString animation;

	float gravity;

	bool able_to_jump = false;

	float jumpStart = 0;

	float jumpHeight = 100;

	float floor = 400.0f;

	int boxW = 40;
	int boxH = 70;

	SDL_Rect playerBox;

	p2Point<float> positionP1;
	p2Point<float> prevpositionP1; 

	PlayerState playerState;

	Collider*	collider;

	bool drop_plat; //Checks if the player is dropping from a platform.

	bool playerGrounded;
	p2Point<float> lastGroundedPos;

	inline void SetGroundState(bool state) 
	{
		if (playerGrounded == true) {
			lastGroundedPos = positionP1;
		}
		playerGrounded = state;
	};

};

class j1Player : public j1Module {
public:// methods

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

	void MoveRight();

	void MoveLeft();

	// Collision handling -----
	void j1Player::OnCollision(Collider* A, Collider* B);
private:

	
public://variables

	Player player;
	

private:

	float frames = 0;

	bool runFrames = false;

	float time = 0.0f;

	float startTime = 0.0f;

	//j1Input playerInput;
};


#endif
