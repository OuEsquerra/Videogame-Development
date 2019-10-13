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
	return true;
}; 

bool j1Player::Start() 
{

	player.positionP1 = {100.0f,player.floor };
	player.playerBox = { (int)player.positionP1.x,(int)player.positionP1.y,player.boxW,player.boxH };

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
			player.playerState = runningRight;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			player.playerState = runningLeft;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) 
	{
		if (player.able_to_jump)
		{
			player.playerState = jumping;
			player.speed.y = 0;
			player.able_to_jump = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		player.drop_plat = true;
	}
	else {
		player.drop_plat = false;
	}
	return true;
};

bool j1Player::Update(float dt) 
{

	time +=  1 / 60;

	player.prevpositionP1 = player.positionP1;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		MoveRight();
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		MoveLeft();
	}
	switch (player.playerState)
	{
	case idle:
		player.animation = "idle";
		player.speed.x = 0;
		break;

	case runningRight:
		player.animation = "run";
		break;

	case runningLeft:
		break;

	case crouch:
		player.animation = "crouch";

		break;
	case jumping:
		
		player.speed.y -= player.acceleration.y;
		//player.SetGroundState(false);
		player.jumping = true;
		LOG("Player y acceleration: %f   Player y speed: %f", player.acceleration.y, player.speed.y);
		break;

	case falling:
		player.jumping = true;
		break;
	
	}

	if (player.jumping)
	{
		player.speed.y += player.gravity; // Speed is +gravity when not grounded
		if (player.speed.y >= player.maxSpeed.y)
		{
			player.speed.y = player.maxSpeed.y;
		}

		if (player.speed.y < 0) 
		{
			player.animation = "jump";
		}
		else 
		{
			player.animation = "fall";
		}
	}
	
	
	
	if(player.playerGrounded)
	{
		player.able_to_jump = true;
		player.playerState = idle;
		player.jumping = false;
	}
	else 
	{
		player.playerState = falling;
	}

	
	player.positionP1.y += player.speed.y;

	player.playerBox.x = player.positionP1.x;
	player.playerBox.y = player.positionP1.y;

	App->map->DrawAnimation(player.animation,"Adventurer"); //We'll send the animation we need
	
	
	
	//Update Player Collider after updating its position
	player.collider->SetPos(player.positionP1.x, player.positionP1.y);
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
		if (player.prevpositionP1.y < B->rect.y || player.positionP1.y == B->rect.y - player.collider->rect.h + 1) {
			player.positionP1.y = B->rect.y - player.collider->rect.h + 1;
			player.SetGroundState(true);
		}
		//from below
		else if (player.prevpositionP1.y > (B->rect.y + B->rect.h)) {
			player.positionP1.y = B->rect.y + B->rect.h;
		}
		//from a side
		//if ((player.positionP1.y+player.collider->rect.h) > B->rect.y || player.positionP1.y < (B->rect.y + B->rect.h)) {
		else if ((player.positionP1.x < B->rect.x + B->rect.w && player.positionP1.x > B->rect.x) ||
			(player.positionP1.x + player.collider->rect.w < B->rect.x + B->rect.w && player.positionP1.x + player.collider->rect.w > B->rect.x)) {
			LOG("Touching WALL");
			//if ((player.prevpositionP1.x + player.collider->rect.w) < B->rect.x) {
			if ((player.positionP1.x + player.collider->rect.w) < (B->rect.x + B->rect.w / 2)) { //Player to the left 
				player.positionP1.x = B->rect.x - player.collider->rect.w;
			}
			else if (player.positionP1.x < (B->rect.x + B->rect.w)) {
				player.positionP1.x = B->rect.x + B->rect.w;
			}
		}



		//player.positionP1.y = B->rect.y - player.collider->rect.h - 9;
		//player.SetGroundState(true);
		
	}


	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {
		
		if (player.drop_plat == false ) {
			if ((player.positionP1.y >= player.prevpositionP1.y)) {
				player.positionP1.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
			}
		}

	}
}

void j1Player::MoveRight()
{
player.speed.x += player.acceleration.x;

if (player.speed.x > player.maxSpeed.x)
{
	player.speed.x = player.maxSpeed.x;
}

player.positionP1.x += player.speed.x; // Move Right at Speed
}

void j1Player::MoveLeft()
{

	player.speed.x -= player.acceleration.x; //non linear acceleration

	if (player.speed.x < -player.maxSpeed.x)
	{
		player.speed.x = -player.maxSpeed.x;
	}

	player.positionP1.x += player.speed.x; // Move Left at Speed
}