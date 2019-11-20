#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"

struct Collider;

enum PlayerState {
	idle,
	running,
	jumping,
	falling,
	crouch,
	dashLeft,
	dashRight
};

struct Player {
	


	p2Point<float> acceleration;
	p2Point<float> speed;
	p2Point<float> maxSpeed;
	p2Point<float> position;
	p2Point<float> prevposition;
	p2Point<float> lastGroundedPos;

	p2SString animation;

	float gravity; 

	bool able_to_jump; //Only lets the player jump if it's true
	bool able_to_dash;
	bool dashing;
	bool jumping; //True when the player is jumping
	bool drop_plat; //Checks if the player is dropping from a platform.
	bool playerGrounded;
	bool flip;
	bool godMode;
	bool cealing;
	bool wall;
	bool onPlatform;
	bool movingRight;
	bool movingLeft;
	bool justLoaded;

	bool freeze = false;

	int boxW;
	int boxH;
	int boxOffset_x;

	SDL_Rect playerBox;
	PlayerState playerState;
	Collider*	collider;

	inline void SetGroundState(bool state) 
	{
		if (playerGrounded == true) 
		{
			lastGroundedPos = position;
		}
		playerGrounded = state;
	};
};

class j1Player : public j1Module {
public:// methods

	j1Player();

	// Destructor
	virtual ~j1Player();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	bool Init();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	//Actions and Checks functions
	void check_x_move(float dt);
	void MoveRight(float dt);
	void MoveLeft(float dt);
	void MoveUp(float dt);
	void MoveDown(float dt);
	void DashInput();
	void RunCheck();
	void JumpInput();
	void Jump();
	void Fall();

	void GodMode();
	bool StartPlayer();
	bool Dash();

	// Collision handling -----
	void j1Player::OnCollision(Collider* A, Collider* B);

private:

public://variables

	Player player;
	
private:

	bool jump_key_down = false;
	float jump_key_down_timer = 0.0f;
	float gravity_tmp = 0;
	float dashTime  = 0.0f;
	int jumpSound = 1;

	//Flying enemy stuff
	SDL_Rect enemy_box = { 20,1200,62,60 };

};


#endif
