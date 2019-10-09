#include "j1App.h"
#include "j1Player.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Render.h"


	bool j1Player::Init() {
	
		return true;
	};

	bool j1Player::Awake(pugi::xml_node config) {


		return true;
	}; 

	bool j1Player::Start() {

		positionP1 = { 100,100 };
		playerBox = { positionP1.x,positionP1.y,100,100 };


		return true;
	};

	bool j1Player::preUpdate() {



		return true;
	};

	bool j1Player::Update() {
	
		App->render->DrawQuad(playerBox,255,0,0,100);
		return true;
	};

	bool j1Player::postUpdate() {

		return true;
	};

	bool j1Player::cleanUp() {

		return true;
	};

