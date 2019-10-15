#include "j1App.h"
#include "j1Player.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Animation.h"
#include "j1Collisions.h"
#include "p2Log.h"

j1Player::j1Player() 
{

	name.create("player");

};

j1Player::~j1Player() 
{


};

bool j1Player::Init() 
{
	
	return true;
};

bool j1Player::Awake(pugi::xml_node& conf) 
{
	player.acceleration.x = conf.child("acceleration").attribute("x").as_float();
	player.acceleration.y = conf.child("acceleration").attribute("y").as_float();
	player.speed.x = conf.child("speed").attribute("x").as_float();
	player.speed.y = conf.child("speed").attribute("y").as_float();
	player.maxSpeed.x = conf.child("maxSpeed").attribute("x").as_float();
	player.maxSpeed.y = conf.child("maxSpeed").attribute("y").as_float();
	player.gravity = conf.child("gravity").attribute("value").as_float();
	player.boxW = conf.child("box").attribute("w").as_int();
	player.boxH = conf.child("box").attribute("h").as_int();
	return true;
}; 

bool j1Player::Start() 
{

	player.position = {100.0f,400.0f }; //Starting position

	player.playerBox = { (int)player.position.x,(int)player.position.y,player.boxW,player.boxH };

	player.collider = App->collisions->AddCollider(player.playerBox, ObjectType::PLAYER, this);

	bool LoadAnimation("player.tmx");

	return true;
};

bool j1Player::PreUpdate() 
{
	player.SetGroundState(false);
	
	if (player.playerState != jumping && player.playerState != falling)
	{
		player.playerState = idle;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			player.playerState = crouch;
			player.drop_plat = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			player.playerState = running;
			player.flip = false;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			player.playerState = running;
			player.flip = true;
		}
	}

	if (!player.godMode)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (player.able_to_jump)
			{
				player.playerState = jumping;
				player.speed.y = 0;

			}
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) //If player has to drop from platform
	{
		player.drop_plat = true;
	}
	else 
	{
		player.drop_plat = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) // Able/Disable GodMode
	{
		GodMode();
	}
	return true;
};

bool j1Player::Update(float dt)
{
	player.prevposition = player.position;

	
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			MoveRight();
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			MoveLeft();
		}

	if (!player.godMode)
	{

		if (!player.godMode)
		{
			switch (player.playerState)
			{
			case idle:
				player.animation = "idle";
				player.speed.x = 0;
				break;

			case running:
				player.animation = "run";
				break;

			case crouch:
				player.animation = "crouch";

				break;
			case jumping:

				player.speed.y -= player.acceleration.y;
				player.jumping = true;
				player.able_to_jump = false;
				LOG("Player y acceleration: %f   Player y speed: %f", player.acceleration.y, player.speed.y);
				break;

			case falling:
				player.jumping = true;
				player.able_to_jump = false;

				break;
			}
		}

		//Logic for when player is jumping
		if (player.jumping)
		{
			player.speed.y += player.gravity; // Speed.y is +gravity when not grounded

			if (player.speed.y >= player.maxSpeed.y) // Speed.y is capped an maxSpeed
			{
				player.speed.y = player.maxSpeed.y;
			}

			if (player.speed.y < 0) // If on jump is going up uses jump animation
			{
				player.animation = "jump";
			}
			else // If on jump is going down uses fall animation
			{
				player.animation = "fall";
			}
		}

		// Grounded logic to check some bools and states
		if (player.playerGrounded)
		{
			player.able_to_jump = true;
			player.playerState = idle;
			player.jumping = false;
		}
		else
		{

			player.playerState = falling;

		}

		player.position.y += player.speed.y;
	}
	else
	{
		player.animation = "idle";
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			MoveUp();
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			MoveDown();
		}
	}

	//Update player collider and position
	//player.position.y += player.speed.y;
	player.playerBox.x = player.position.x;
	player.playerBox.y = player.position.y;

	//Draw player
	App->map->DrawAnimation(player.animation,"Adventurer",player.flip);
	
	//Update Player Collider after updating its position
	player.collider->SetPos(player.position.x, player.position.y);
	return true;
	
};

bool j1Player::PostUpdate() 
{

	return true;
};

bool j1Player::cleanUp() 
{

	return true;
};

void j1Player::OnCollision(Collider* A, Collider* B) {

	if (B->type == ObjectType::PLAYER) {
		Collider temp = *A;
		A = B;
		B = &temp;
	}
	if (A->type != ObjectType::PLAYER) {
		return;
	}

	// ------------ Player Colliding against solids ------------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::SOLID) {

		//from above
		if (player.prevposition.y < B->rect.y || player.position.y == B->rect.y - player.collider->rect.h + 1) {
			player.position.y = B->rect.y - player.collider->rect.h + 1;
			player.SetGroundState(true);
		}
		//from below
		else if (player.prevposition.y > (B->rect.y + B->rect.h)) {
			player.position.y = B->rect.y + B->rect.h;
		}
		//from a side
		else if ((player.position.x < B->rect.x + B->rect.w && player.position.x > B->rect.x) ||
			(player.position.x + player.collider->rect.w < B->rect.x + B->rect.w && player.position.x + player.collider->rect.w > B->rect.x)) {
			LOG("Touching WALL");
			if ((player.position.x + player.collider->rect.w) < (B->rect.x + B->rect.w / 2)) { //Player to the left 
				player.position.x = B->rect.x - player.collider->rect.w;
			}
			else if (player.position.x < (B->rect.x + B->rect.w)) {
				player.position.x = B->rect.x + B->rect.w;
			}
		}
	}


	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {
		
		if (player.drop_plat == false ) {
			if ((player.prevposition.y + player.collider->rect.h) < B->rect.y + (B->rect.h/2.0f) && (player.prevposition.y + player.collider->rect.h) > B->rect.y) {//this won't ever happen
				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
			}
			else if ((player.position.y >= player.prevposition.y) && (player.prevposition.y + player.collider->rect.h) < B->rect.y) {
				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
			}
		}

	}
}

void j1Player::MoveRight() // Move Right the player at set speed
{
	player.speed.x += player.acceleration.x;

	if (player.speed.x > player.maxSpeed.x)
	{
		player.speed.x = player.maxSpeed.x;
	}
	player.position.x += player.speed.x; 
}

void j1Player::MoveLeft() // Move Left the player at speed
{
	player.speed.x -= player.acceleration.x; 

	if (player.speed.x < -player.maxSpeed.x)
	{
		player.speed.x = -player.maxSpeed.x;
	}
	player.position.x += player.speed.x; 
}

void j1Player::MoveDown() // Move Right the player at set speed
{
	

	player.position.y += player.maxSpeed.y;
}

void j1Player::MoveUp() // Move Right the player at set speed
{
	
	
	
	
	player.position.y -= player.maxSpeed.y;
}
void j1Player::GodMode()
{
	if (player.godMode)
	{
		player.godMode = false;
	}
	else
	{
		player.godMode = true;
	}
}