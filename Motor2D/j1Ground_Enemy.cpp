
#include "j1App.h"
#include "j1Map.h"
#include "SDL/include/SDL_rect.h"


#include "j1EntityMachine.h"

//Flying Enemy
Ground_Enemy::Ground_Enemy(float x, float y, EntityType Type) : Entity(x, y, Type)
{
	colliderRect = { position.x, position.y, 32, 64 }; //Magic
	collider = App->collisions->AddCollider(colliderRect, ObjectType::ENEMY, App->entities,(Entity*)this);
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


	position.x = 500.0f;

	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
	}
	//Draw enemy
	App->map->DrawAnimation("idle", "Skeleton", position , Ainfo, false);

	return true;
}