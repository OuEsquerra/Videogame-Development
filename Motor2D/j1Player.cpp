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

	positionP1 = {200,500 };
	playerBox = { positionP1.x,positionP1.y,50,100 };


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
	


	return true;
};

bool j1Player::Update(float dt) {

	switch (playerState) {

	case idle:

		break;

	case runningRight:
		positionP1.x += 1; // Move Right at Speed
		break;

	case runningLeft:
		positionP1.x -= 1; // Mode Left at Speed
		break;

	case jumping:

		break;
	}

	playerBox.x = positionP1.x;
	App->render->DrawQuad(playerBox,200,200,0);
	return true;
};

bool j1Player::PostUpdate() {

	return true;
};

bool j1Player::cleanUp() {

	return true;
};

