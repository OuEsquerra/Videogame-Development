#include "j1App.h"
#include "j1Player.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1FadeToBlack.h"
#include "p2Animation.h"
#include "j1Collisions.h"
#include "p2Log.h"
#include "j1Audio.h"

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
	player.speed.x =		conf.child("speed").attribute("x").as_float();
	player.speed.y =		conf.child("speed").attribute("y").as_float();
	player.maxSpeed.x =		conf.child("maxSpeed").attribute("x").as_float();
	player.maxSpeed.y =		conf.child("maxSpeed").attribute("y").as_float();
	player.gravity =		conf.child("gravity").attribute("value").as_float();
	player.boxW =			conf.child("box").attribute("w").as_int();
	player.boxH =			conf.child("box").attribute("h").as_int();
	player.boxOffset_x =	conf.child("offset").attribute("x").as_int();

	App->audio->LoadFx("audio/fx/jump1.wav");
	App->audio->LoadFx("audio/fx/jump2.wav");
	App->audio->LoadFx("audio/fx/jump3.wav");
	App->audio->LoadFx("audio/fx/sword_sound.wav");

	gravity_tmp = player.gravity;
	
	return true;
}; 
 
bool j1Player::Start()
{
	StartPlayer();

	dashtimercheck = new j1PerfTimer;
	jump_key_down_timer = new j1PerfTimer;

	return true;
};

bool j1Player::PreUpdate()
{

	if (player.freeze == true) //If the player is frozen, Logic won't be updated
	{
		return true;
	} 

	player.SetGroundState(false);

	if (player.playerState != jumping && player.playerState != falling && !player.dashing) //If player is not in any major state idle by default and checks for left/right input
	{
		player.playerState = idle;
		RunCheck();
	}

	if (!player.godMode && !player.dashing)
	{
		JumpInput();
	}

	if (player.able_to_dash && !player.dashing) //Logic For when player can dash
	{
		DashInput();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) //If player has to drop from platform
	{
		player.drop_plat = true;
	}
	else 
	{
		player.drop_plat = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) // Able/Disable GodMode
	{
		GodMode();
	}

	return true;
};

bool j1Player::Update(float dt)
{
	

	player.prevposition = player.position;

	if (App->do_logic)
	{
		dashTime += 1;
	}

	if (player.freeze == true) //If the player is frozen, Logic won't be updated
	{
		return true;
	}
	
	player.prevposition = player.position;

	if (player.cealing || player.onPlatform && !player.jumping)
	{
		player.speed.y = 0;
	}

	if (!player.dashing)
	{
		check_x_move(dt);
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

				Jump();
				
				break;
			case falling:

				Fall();

				break;
			case dashLeft:

				Dash();

				break;
			case dashRight:

				Dash();

				break;
			}
		}
		
		// Grounded logic to check some bools and states
		if (player.playerGrounded || player.onPlatform)
		{
			player.able_to_jump = true;
			player.jumping = false;

			if (!player.dashing)
			{
				player.able_to_dash = true;
				player.playerState = idle;
			}
		}
		else //When not touching ground and dashing, fall
		{
			if (!player.dashing)
			{
				player.playerState = falling;
			}
		}

		if (player.speed.y >= player.maxSpeed.y*dt) // Speed.y is capped at maxSpeed
		{
			player.speed.y = player.maxSpeed.y*dt;
		}
		
		player.position.x += player.speed.x;
		
		if (player.wall)
		{
			player.speed.x = 0;
		}
		
	}
	else //When GodMode is active
	{
		player.animation = "idle";

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			MoveUp(dt);
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			MoveDown(dt);
		}
		player.position.x += player.speed.x * 2 * dt;
	}

	//Update player collider and position
	player.playerBox.x = player.position.x;
	player.playerBox.y = player.position.y;

	//Draw player
	App->map->DrawAnimation(player.animation,"Adventurer",&player.playerBox,player.flip);

	//Update Player Collider after updating its position
	player.collider->SetPos(player.position.x + player.boxOffset_x, player.position.y);

	player.cealing = false;
	player.wall = false;
	player.onPlatform = false;

	return true;
};

bool j1Player::PostUpdate() 
{
	if (player.freeze == true) //If the player is frozen, Logic won't be updated
	{
		return true;
	}

	if (player.justLoaded == true) { //This has to be switched after collisions, hence the post-update.
		player.justLoaded = false;
	}

	return true;
};

bool j1Player::CleanUp() 
{
	return true;
};

bool j1Player::StartPlayer() {

	if(App->fade->playerReset == true)

	player.position = App->map->data.start_position;

	player.playerBox = { (int)player.position.x,(int)player.position.y,player.boxW,player.boxH };

	player.collider = App->collisions->AddCollider(player.playerBox, ObjectType::PLAYER, this);

	player.able_to_jump = false; //Only lets the player jump if it's true
	player.able_to_dash = false;
	player.dashing = false;
	player.jumping = false; //True when the player is jumping
	player.drop_plat; //Checks if the player is dropping from a platform.
	player.flip = false;
	player.godMode = false;
	player.cealing = false;
	player.wall = false;
	player.onPlatform = false;
	player.movingRight = false;
	player.movingLeft = false;
	player.justLoaded = false;
	
	return true;
}

void j1Player::OnCollision(Collider* A, Collider* B) {

	if (player.godMode) return; //While in God Mode Collisions are disregarded
	
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
		if (player.position.y + A->rect.h > B->rect.y
			&& player.position.y < B->rect.y
			&& A->rect.x < B->rect.x + B->rect.w
			&& A->rect.x + A->rect.w > B->rect.x
			&& player.prevposition.y + player.boxH <= B->rect.y + 1 //MagicNumber
			&& player.justLoaded == false)
		{
			if (player.speed.y > 0)
			{
				player.speed.y = 0;
			}
			player.position.y = B->rect.y - player.collider->rect.h + 1;
			player.collider->SetPos(player.position.x + player.boxOffset_x, player.position.y);
			player.SetGroundState(true);
		}

		//from below
		if (player.prevposition.y > (B->rect.y + B->rect.h - 1)) 
		{
			player.position.y = B->rect.y + B->rect.h ;
			player.cealing = true;
			player.collider->SetPos(player.position.x + player.boxOffset_x, player.position.y);
		}

		//from a side
		if (player.position.y + (A->rect.h* 0.1f) < B->rect.y + B->rect.h  
			&& player.position.y + (A->rect.h* 0.9f) > B->rect.y ) 
		{
			player.wall = true;
			LOG("Touching WALL");

			if ((A->rect.x + A->rect.w) < (B->rect.x + B->rect.w / 4)) 
			{ //Player to the left 
				player.position.x = B->rect.x -A->rect.w - player.boxOffset_x  +1;

			}
			else if (A->rect.x  > (B->rect.x + B->rect.w*3/4)) 
			{ //Player to the right
				player.position.x = B->rect.x + B->rect.w - player.boxOffset_x - 1; 
			}
			player.collider->SetPos(player.position.x + player.boxOffset_x, player.position.y);
		}
	}
	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {
		
		if (player.drop_plat == false ) {

			if ((player.prevposition.y + player.collider->rect.h) < B->rect.y + (B->rect.h / 2.0f) && (player.prevposition.y + player.collider->rect.h) > B->rect.y && player.speed.y >= 0) {//this won't ever happen
				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
				player.onPlatform = true;
			}
			else if ((player.position.y >= player.prevposition.y) && (player.prevposition.y + player.collider->rect.h) < B->rect.y && player.speed.y >= 0) {
				player.position.y = B->rect.y - player.collider->rect.h + 1;
				player.SetGroundState(true);
				player.able_to_jump = false;
				player.onPlatform = true;
			}
		}

	}
	// ------------ Player Colliding against a warp zone -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::WARP) {
		App->fade->FadeToBlack(B->userdata->Get("MapToLoad").v_string);
	}
}

void j1Player::check_x_move(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		player.movingRight = true;
		MoveRight(dt);
		player.flip = false;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		player.movingLeft = true;
		MoveLeft(dt);
		player.flip = true;
	}
	else
	{
		player.speed.x = 0;
	}
}

void j1Player::JumpInput()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) //Jump if not on godmode
	{
		if (player.able_to_jump)
		{
			//jumpSound = rand() % 3 + 1; //Fix
			//App->audio->PlayFx(jumpSound, 0);//Sound for the start of the jump

			player.playerState = jumping;
			jump_key_down = true;
			jump_key_down_timer->Start();
			player.speed.y =0 ;
		}
		//player.gravity = gravity_tmp / 2;
	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && jump_key_down && jump_key_down_timer->ReadMs() < 250.0f && !player.dashing)
	{
		//player.gravity = gravity_tmp * 0.75;
		player.playerState = jumping;
		jump_key_down = true;
	}
	else
	{
		jump_key_down = false;
		//player.gravity = gravity_tmp;
	}
}

void j1Player::DashInput()
{
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		App->audio->PlayFx(4, 0);

		if (player.flip || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			player.playerState = dashLeft;
		}
		else if(!player.flip || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			player.playerState = dashRight;
		}

		dashTime = 0;

		dashtimercheck->Start();

		player.able_to_dash = false;
	}
}

void j1Player::RunCheck()
{
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		player.playerState = crouch;
		player.drop_plat = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT
		|| App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT
		|| App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT
		|| App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		player.playerState = running;
	}
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

bool j1Player::Dash()
{
	
	player.animation = "dash";

	if (!player.wall)
	{
		if (player.playerState == dashLeft)
		{
			player.speed.x = -player.maxSpeed.x * 2 * App->dt;
		}
		else
		{
			player.speed.x = player.maxSpeed.x * 2 * App->dt;
		}
	}
	player.dashing = true;
	//Dash Check
	if (dashtimercheck->ReadMs() >= 200.0f)
	{
		player.playerState = falling;
		player.dashing = false;
		player.speed.y = 0;

		LOG("Dash took: %lf", dashtimercheck->ReadMs());
	}
	return true;
}

void j1Player::Jump()
{
	player.animation = "jump";
	player.jumping = true;
	player.able_to_jump = false;

	//Logic for when player is jumping
	if (player.speed.y > 0) // If on jump is going up uses jump animation
	{
		player.playerState = falling;
	}

	player.speed.y -= player.acceleration.y * App->dt;
	player.speed.y += (player.gravity * App->dt) * 0.75; // Speed.y is +gravity when not grounded
	player.position.y += player.speed.y; //Update position y
}

void j1Player::Fall()
{
	player.animation = "fall";
	player.jumping = true;
	player.able_to_jump = false;

	player.speed.y += player.gravity*  App->dt; // Speed.y is +gravity when not grounded
	player.position.y += player.speed.y; //Update position y
}

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

	player.justLoaded = true;

	pugi::xml_node points = node.child("points");

	player.position.x = points.child("position").attribute("x").as_float();
	player.position.y = points.child("position").attribute("y").as_float();

	player.prevposition.x = points.child("prevposition").attribute("x").as_float();
	player.prevposition.y = points.child("prevposition").attribute("y").as_float();

	player.lastGroundedPos.x = points.child("lastGroundedPos").attribute("x").as_float();
	player.lastGroundedPos.y = points.child("lastGroundedPos").attribute("y").as_float();

	pugi::xml_node flags = node.child("flags");
	player.able_to_dash = flags.attribute("able_to_dash").as_bool();
	player.able_to_jump = flags.attribute("able_to_jump").as_bool();
	player.drop_plat = flags.attribute("drop_plat").as_bool();
	player.dashing = flags.attribute("dashing").as_bool();
	player.jumping = flags.attribute("jumping").as_bool();
	player.playerGrounded = flags.attribute("playerGrounded").as_bool();

	player.playerState = (PlayerState)node.attribute("playerstate").as_int();

	return true;
}

void j1Player::MoveRight(float dt) // Move Right the player at set speed
{
	player.speed.x += player.acceleration.x * dt;

	if (player.speed.x > player.maxSpeed.x*dt)
	{
		player.speed.x = player.maxSpeed.x * dt;
	}

}

void j1Player::MoveLeft(float dt) // Move Left the player at speed
{
	player.speed.x -= player.acceleration.x*dt;

	if (player.speed.x < -player.maxSpeed.x*dt)
	{
		player.speed.x = -player.maxSpeed.x*dt;
	}
}

void j1Player::MoveDown(float dt) // Move Right the player at set speed
{
	player.position.y += player.maxSpeed.y*dt;
}

void j1Player::MoveUp(float dt) // Move Right the player at set speed
{
	player.position.y -= player.maxSpeed.y*dt;
}