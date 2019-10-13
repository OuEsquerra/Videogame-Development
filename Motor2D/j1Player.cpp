#include "j1App.h"
#include "j1Player.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Animation.h"
#include "j1Collisions.h"

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
	player.acceleration = conf.child("acceleration").attribute("value").as_float();

	player.speedX = conf.child("speedX").attribute("value").as_float();

	player.maxSpeed = conf.child("maxSpeed").attribute("value").as_float();

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
	player.playerState = falling;
	



	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		player.playerState = runningRight;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		player.playerState = runningLeft;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) 
	{
		player.playerState = jumping;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) 
	{
		player.playerState = falling;
		player.drop_plat = true;
	}
	
	return true;
};

bool j1Player::Update(float dt) 
{
	frames++;

	player.prevpositionP1 = player.positionP1;
	if ((player.positionP1.y - player.collider->rect.h) > (player.lastGroundedPos.y + App->collisions->platform_h)) {
		player.drop_plat = false;
	}
	
	switch (player.playerState)
	{

	case idle:

		player.speedX = 0;

		break;

	case runningRight:


		player.speedX += player.acceleration;

		if (player.speedX > player.maxSpeed)
		{
			player.speedX = player.maxSpeed;
		}

		player.positionP1.x += player.speedX; // Move Right at Speed


		break;

	case runningLeft:

		
		player.speedX -= player.acceleration; //non linear acceleration

		if (player.speedX < -player.maxSpeed)
		{
			player.speedX = -player.maxSpeed;
		}

		player.positionP1.x += player.speedX; // Mode Left at -Speed


		break;

	case jumping:


		player.speedY = -player.acceleration*12;

		player.positionP1.y += player.speedY*5;
		 
		player.SetGroundState(false);
		break; 	
	}

	//The player is falling
	if (player.playerGrounded == false) {

		player.speedY += player.acceleration;

		if (player.speedY > player.maxSpeed)
		{
			player.speedY = player.maxSpeed;
		}

		player.positionP1.y += player.speedY;

	}


	player.playerBox.x = player.positionP1.x;

	//App->render->DrawQuad(player.playerBox,255,200,0);

	/*if (player.positionP1.y <= player.floor) 
	{
		player.positionP1.y = player.floor;
	}*/
	if (player.playerState == falling) 
	{
		App->map->DrawAnimation("idle","adventurer 64"); //we'll send the animation we need
		
	}
	if (player.playerState == runningRight)
	{
		//Update Player Collider after updating its position
		App->map->DrawAnimation("running", "adventurer 64");
	}
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
		else if((player.positionP1.x < B->rect.x + B->rect.w && player.positionP1.x > B->rect.x) || 
			(player.positionP1.x + player.collider->rect.w < B->rect.x + B->rect.w && player.positionP1.x + player.collider->rect.w > B->rect.x)){
			LOG("Touching WALL");
			//if ((player.prevpositionP1.x + player.collider->rect.w) < B->rect.x) {
			if ((player.positionP1.x + player.collider->rect.w) < (B->rect.x + B->rect.w/2)) { //Player to the left 
				player.positionP1.x = B->rect.x - player.collider->rect.w;
			}
			else if (player.positionP1.x < (B->rect.x + B->rect.w)) {
				player.positionP1.x = B->rect.x + B->rect.w;
			}
		}
	
		
	}


	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {
		if (player.drop_plat == false) {
			if (player.positionP1.y >= player.prevpositionP1.y) {
				player.positionP1.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
			}
		}
	}

}

