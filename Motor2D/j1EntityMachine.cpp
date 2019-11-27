
#include "j1App.h"
#include "j1EntityMachine.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Map.h"
#include "j1Flying_Enemy.h"

bool j1EntityMachine::Save(pugi::xml_node& conf) const {
	return true;
};
bool j1EntityMachine::Load(pugi::xml_node& conf) {
	return true;
};

j1EntityMachine::j1EntityMachine() {
	name.create("entities");
};

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
Entity* j1EntityMachine::CreateEntity(float x, float y,SDL_Rect* Rect, EntityType Type) {
	
	static_assert(EntityType::UNKNOWN == 5, " Something broke :( ");
	
	Entity* ret = nullptr;
	
	switch (Type) {
		case PLAYER: 

			//ret = new Player(x, y, Rect, Type); //Struct Player es igual
			
		break;
		
		case PARTICLE:
			//ret = new Particle(x,y,Rect,Type);
		break;
		
		case FLYING_ENEMY: 
			//ret = ;

			flying_enemy = new Flying_Enemy(x, y, Rect, Type);

			if (ret != nullptr)
			{
				entity_list->add(ret);
			}
		break;
		
		case GROUND_ENEMY: 
			//ret = new Enemy_ground(x, y, Rect, Type);
		break;
	}

	entity_list->add(ret);

	return ret;
};


// Destroy an Entity and remove it from the list -----------------------------------------------------
void j1EntityMachine::DeleteEntity(Entity* entity) {

	delete entity->rect;

	entity_list->del(entity_list->At(entity_list->find(entity)));
}


//Entity Methods

Entity::Entity(float x, float y,SDL_Rect* rect, EntityType Type) : position(x,y),rect(rect),type(Type)
{

}


bool Entity::Awake(pugi::xml_node&)
{
	return true;
}
bool Entity::Start()
{
	return true;
}

bool Entity::Update(float dt)
{
	return true;
}

bool Entity::PostUpdate()
{
	return true;
}

bool Entity::PreUpdate()
{
	return true;
}

bool Entity::CleanUp()
{
	return true;
}

bool Entity::Load(pugi::xml_node &)
{
	return true;
}

bool Entity::Save(pugi::xml_node &)
{
	return true;
}

//Flying Enemy
Flying_Enemy::Flying_Enemy(float x, float y, SDL_Rect* rect, EntityType Type) : Entity(x, y, rect, Type)
{

}

bool Flying_Enemy::Awake(pugi::xml_node &)
{

	return true;
}

bool Flying_Enemy::Start()
{

	return true;
}

bool Flying_Enemy::Update()
{

	return true;
}