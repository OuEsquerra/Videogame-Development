#include "j1App.h"
#include "j1Player.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Input.h"

j1Player::j1Player() {

	name.create("player");

};

j1Player::~j1Player() {


};

bool j1Player::Init() {
	
	return true;
};

bool j1Player::Awake(pugi::xml_node config) {


	return true;
}; 

bool j1Player::Start() {

	positionP1 = {200.0f,500.0f };
	playerBox = { (int)positionP1.x,(int)positionP1.y,boxW,boxH };


	return true;
};

bool j1Player::PreUpdate() {
	
	playerState = idle;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		playerState = runningRight;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		playerState = runningLeft;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) {
		playerState = jumping;
	}
	
	return true;
};

bool j1Player::Update(float dt) {
	float a = 0.3f;

	switch (playerState) {

	case idle:
		accelerationFrames = 0;

		break;

	case runningRight:



		
		positionP1.x += playerSpeed; // Move Right at Speed
		
		accelerationFrames++;

		break;

	case runningLeft:
		positionP1.x -= playerSpeed; // Mode Left at Speed
		break;

	case jumping:

		break;
	}

	playerBox.x = positionP1.x;

	App->render->DrawQuad(playerBox,255,200,0);


	return true;
	
};

bool j1Player::PostUpdate() {

	return true;
};

bool j1Player::cleanUp() {

	return true;
};

