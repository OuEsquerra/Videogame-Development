
#include "j1App.h"
#include "j1Map.h"
#include "SDL/include/SDL_rect.h"

#include "j1EntityMachine.h"

//Flying Enemy
Ground_Enemy::Ground_Enemy(float x, float y, SDL_Rect* rect, EntityType Type) : Entity(x, y, rect, Type)
{

}

bool Ground_Enemy::Awake(pugi::xml_node &)
{

	return true;
}

bool Ground_Enemy::Start()
{

	return true;
}

bool Ground_Enemy::Update(float dt)
{

	rect->x = position.x;
	rect->y = position.y;

	//Draw enemy
	App->map->DrawAnimation("skull_still", "Skull1", rect, false);

	return true;
}