
#include "j1App.h"
#include "j1Map.h"
#include "SDL/include/SDL_rect.h"

#include "j1Pathfinding.h"
#include "j1EntityMachine.h"

//Flying Enemy
Ground_Enemy::Ground_Enemy(float x, float y, EntityType Type) : Entity(x, y, Type)
{
	colliderRect = { position.x, position.y, 32, 64 }; //Magic
	collider = App->collisions->AddCollider(colliderRect, ObjectType::ENEMY, App->entities,(Entity*)this);

	speed = { 150,150 };
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
	prevposition = position;

	/*if (App->do_logic)
	{*/
		pathfind();
	//}

	if (!grounded)
	{

		//Pathfinding -------------------------------------------
		goal = App->entities->player->position;

		if (goal.DistanceTo(position) < 1000) { //Detection radius

			//Find the closest tile to current position
			App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(goal.x, goal.y));

			const p2DynArray<iPoint>* Path = App->pathfinding->GetLastPath();
			//LOG("PATH COUNT: %d", Path->Count());

			const iPoint* tile;
			if (Path->Count() != 0) {
				if (Path->Count() > 1) {
					tile = Path->At(1);
				}
				else
				{
					tile = Path->At(0);
				}

				iPoint closest_center = App->map->MapToWorldCentered(tile->x, tile->y);

				if (closest_center.x > position.x) {
					position.x += 1;
					flip = false;
				}
				else if (closest_center.x < position.x) {
					position.x -= 1;
					flip = true;
				}
				
				
			}
		}

		position.y += 150 * dt;

	}





	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
	}
	//Draw enemy
	App->map->DrawAnimation("idle", "Skeleton", position , Ainfo, flip);

	grounded = false;

	return true;
}

void Ground_Enemy::pathfind()
{
	//Pathfinding -------------------------------------------
	goal = App->entities->player->position;

	if (goal.DistanceTo(position) < 1000) { //Detection radius

		//Find the closest tile to current position
		App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(goal.x, goal.y));

		const p2DynArray<iPoint>* Path = App->pathfinding->GetLastPath();
		LOG("PATH COUNT: %d", Path->Count());

		const iPoint* tile;
		if (Path->Count() != 0) {
			if (Path->Count() > 1) {
				tile = Path->At(1);
			}
			else
			{
				tile = Path->At(0);
			}

			iPoint closest_center = App->map->MapToWorldCentered(tile->x, tile->y);

			if (closest_center.x > position.x) {
				position.x += speed.x * App->dt;
				flip = true;
			}
			else if (closest_center.x < position.x) {
				position.x -= speed.x * App->dt;
				flip = false;
			}


		}
	}
}