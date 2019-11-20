
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


// Create an Entity and add to the list ----------------------------------------------------
Entity* j1EntityMachine::CreateEntity(SDL_Rect* Rect, SDL_Texture* Tex, EntityType Type) {
	
	static_assert(EntityType::UNKNOWN == 5, " Something broke :( ");
	
	Entity* ret = nullptr;
	
	switch (Type) {
		case PLAYER: 
			//ret = new Player(Rect, Tex, Type);
			
		break;
		
		case PARTICLE:
			ret = new Particle(Type);

		break;
		
		case FLYING_ENEMY: 
			
		break;
		
		case GROUND_ENEMY: 
			
		break;
	}
	

	entity_list->add(ret);

	return ret;
};


// Destroy an Entity and remove it from the list -----------------------------------------------------
void j1EntityMachine::DeleteEntity(Entity* entity) {
	delete entity->texture;
	delete entity->rect;


	entity_list->del(entity_list->At(entity_list->find(entity)));

}