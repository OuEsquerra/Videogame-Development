
#include "j1App.h"
#include "j1EntityMachine.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Map.h"

bool j1EntityMachine::Save(pugi::xml_node& conf) const {
	return true;
};
bool j1EntityMachine::Load(pugi::xml_node& conf) {
	return true;
};



j1EntityMachine::j1EntityMachine() {};
bool j1EntityMachine::Start() {
	return true;
};

bool  j1EntityMachine::Awake(pugi::xml_node&) {
	return true;
};

bool j1EntityMachine::Update(float dt) {
	return true;
};




bool j1EntityMachine::CleanUp() {
	return true;
};