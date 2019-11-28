
#include "j1App.h"
#include "j1Map.h"
#include "SDL/include/SDL_rect.h"

//#include "j1Entity.h"
#include "j1Flying_Enemy.h"

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

bool Flying_Enemy::Update(float dt)
{
	SDL_Rect tmprec = { 100,100,64,64 };
		
	//Draw enemy
	App->map->DrawAnimation("skull_still", "Skull1", &tmprec, false);

	return true;
}