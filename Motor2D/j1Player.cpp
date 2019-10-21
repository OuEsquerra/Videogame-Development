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

bool j1Player::Save(pugi::xml_node& node) const {
	
	LOG("Saving Player...");
	pugi::xml_node points = node.append_child("points");
	
	points.append_child("position").append_attribute("x") = player.position.x;
	points.child("position").append_attribute("y") = player.position.y;
	
	points.append_child("prevposition").append_attribute("x") = player.prevposition.x;
	points.child("prevposition").append_attribute("y") = player.prevposition.y;
	
	points.append_child("lastGroundedPos").append_attribute("x") = player.lastGroundedPos.x;
	points.child("lastGroundedPos").append_attribute("y") = player.lastGroundedPos.y;


	pugi::xml_node flags = node.append_child("flags");
	flags.append_attribute("able_to_jump") = player.able_to_jump;
	flags.append_attribute("able_to_dash") = player.able_to_dash;
	flags.append_attribute("dashing") = player.dashing;
	flags.append_attribute("jumping") = player.jumping;
	flags.append_attribute("drop_plat") = player.drop_plat;
	flags.append_attribute("playerGrounded") = player.playerGrounded;
	flags.append_attribute("flip") = player.flip;
	flags.append_attribute("godMode") = player.godMode;

	node.append_attribute("playerstate") = player.playerState;

	return true;
}

bool j1Player::Load(pugi::xml_node& node) {
	
	LOG("Loading Player...");
	pugi::xml_node points = node.child("points");

	player.position.x = points.child("position").attribute("x").as_float();
	player.position.y = points.child("position").attribute("y").as_float();

	player.prevposition.x = points.child("prevposition").attribute("x").as_float();
	player.prevposition.y = points.child("prevposition").attribute("y").as_float();

	player.lastGroundedPos.x = points.child("lastGroundedPos").attribute("x").as_float();
	player.lastGroundedPos.y = points.child("lastGroundedPos").attribute("y").as_float();
	
	pugi::xml_node flags = node.child("flags");
	player.able_to_dash		= flags.attribute("able_to_dash").as_bool();
	player.able_to_jump		= flags.attribute("able_to_jump").as_bool();
	player.drop_plat		= flags.attribute("drop_plat").as_bool();
	player.dashing			= flags.attribute("dashing").as_bool();
	player.jumping			= flags.attribute("jumping").as_bool();
	player.playerGrounded	= flags.attribute("playerGrounded").as_bool();

	player.playerState = (PlayerState)node.attribute("playerstate").as_int();
	return true;
}

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
	player.speed.x =		conf.child("speed").attribute("x").as_float();
	player.speed.y =		conf.child("speed").attribute("y").as_float();
	player.maxSpeed.x =		conf.child("maxSpeed").attribute("x").as_float();
	player.maxSpeed.y =		conf.child("maxSpeed").attribute("y").as_float();
	player.gravity =		conf.child("gravity").attribute("value").as_float();
	player.boxW =			conf.child("box").attribute("w").as_int();
	player.boxH =			conf.child("box").attribute("h").as_int();
	return true;
}; 

bool j1Player::Start() 
{
	InitPlayer();

	return true;
};



bool j1Player::PreUpdate() 
{
	player.SetGroundState(false);
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		player.flip = false;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		player.flip = true;
	}

	if (player.playerState != jumping && player.playerState != falling && !player.dashing)
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
			//player.flip = false;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			player.playerState = running;
			//player.flip = true;
		}
	}

	if (player.able_to_dash && !player.dashing )
	{
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		{
			if (player.flip)
			{
				player.playerState = dashLeft;
			}
			else
			{
				player.playerState = dashRight;
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				player.playerState = dashRight;
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				player.playerState = dashLeft;
			}
			player.able_to_dash = false;
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
				//player.position.y+=2;
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

	dashTime++;

	if ((player.playerState == dashRight || player.playerState == dashLeft) && !player.dashing)
	{
		//player.dashing = true;
		dashTime = 0;
	}

	if (!player.dashing)
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			MoveRight();
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			MoveLeft();
		}
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

			case dashLeft:

				player.animation = "dash";

				player.speed.x = -player.maxSpeed.x * 3/2;

				player.position.x += player.speed.x;

				player.dashing = true;

				if (dashTime > 10)
				{
					player.playerState = falling;
					player.dashing = false;
					player.speed.y = 0;
				}

				break;

			case dashRight:

				player.animation = "dash";

				player.speed.x = player.maxSpeed.x * 3/2;

				player.position.x += player.speed.x;

				player.dashing = true;

				if (dashTime > 10)
				{
					player.playerState = falling;
					player.dashing = false;
					player.speed.y = 0;
				}
				break;
			}
		}

		// Grounded logic to check some bools and states
		if (player.playerGrounded)
		{
			player.able_to_jump = true;
			player.jumping = false;

			if (!player.dashing)
			{
				player.able_to_dash = true;
				player.playerState = idle;
			}
		}
		else
		{
			if (!player.dashing)
			{
				player.playerState = falling;
			}
		}

		if (!player.dashing)
		{
			player.position.y += player.speed.y;
			/*if (!player.playerGrounded)
			{
				
			}*/
		}

		if (!player.dashing)
		{
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
		}
	}
	else //When GodMode is active
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
	player.playerBox.x = player.position.x;
	player.playerBox.y = player.position.y;

	//Draw player
	App->map->DrawAnimation(player.animation,"Adventurer",player.flip);
	
	//Update Player Collider after updating its position
	player.collider->SetPos(player.position.x + 20, player.position.y);

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


bool j1Player::InitPlayer() {

	player.position = { 250.0f,1100.0f }; //Starting position //Magic Numbers

	player.playerBox = { (int)player.position.x,(int)player.position.y,player.boxW,player.boxH };

	player.collider = App->collisions->AddCollider(player.playerBox, ObjectType::PLAYER, this);
	
	return true;
}


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
	
		/*if (player.prevposition.y < B->rect.y || (player.position.y == B->rect.y - player.collider->rect.h + 1 && player.prevposition.y != player.position.y)) {
			player.position.y = B->rect.y - player.collider->rect.h + 1;
			player.SetGroundState(true);
		}*/
		//from below
		if (player.prevposition.y > (B->rect.y + B->rect.h - 1)) 
		{
			player.position.y = B->rect.y + B->rect.h;
			
		}
		//from a side
		else if (player.position.y + (player.collider->rect.h* 3.0f/4.0f) < B->rect.y + B->rect.h  
			&& player.position.y + (player.collider->rect.h* 3.0f / 4.0f) > B->rect.y ) 
		{
			LOG("Touching WALL");
			if ((player.collider->rect.x + player.collider->rect.w) < (B->rect.x + B->rect.w / 2)) { //Player to the left 
				player.position.x = B->rect.x - player.collider->rect.w -20;
			}
			else if (player.collider->rect.x < (B->rect.x + B->rect.w)) { //Player to the right
				player.position.x = B->rect.x + B->rect.w -20;
			}
		}
		else if (player.position.y < B->rect.y + B->rect.h) { // from above
			LOG("player y = %f", player.position.y);
			LOG("collider y = %d", B->rect.y);
			LOG("collider h = %d", B->rect.h);
			player.speed.y = 0;
			player.position.y = B->rect.y - player.collider->rect.h + 1 ;

			player.SetGroundState(true);
		}
	}


	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {
		
		if (player.drop_plat == false ) {
			if ((player.prevposition.y + player.collider->rect.h) < B->rect.y + (B->rect.h/2.0f) && (player.prevposition.y + player.collider->rect.h) > B->rect.y && player.playerState != jumping) {//this won't ever happen
				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
				player.speed.y = 0;
			}
			else if (player.position.y < B->rect.y + B->rect.h && player.playerState != jumping) {

				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.speed.y = 0;
				//player.able_to_jump = false;
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