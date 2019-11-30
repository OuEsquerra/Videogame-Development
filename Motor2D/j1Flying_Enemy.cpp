
#include "j1App.h"



#include "j1Map.h"
#include "j1Pathfinding.h"
#include "SDL/include/SDL_rect.h"

#include "j1EntityMachine.h"


//Flying Enemy
Flying_Enemy::Flying_Enemy(float x, float y, EntityType Type) : Entity(x, y, Type)
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
	//Pathfinding -------------------------------------------
	goal = App->entities->player->position;

//	if (App->pathfinding->IsWalkable(App->map->WorldToMap(goal.x, goal.y))) {

	//Find the closest tile to current position
	App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(goal.x, goal.y));
		
	p2DynArray<iPoint>* Path = (p2DynArray<iPoint>*)App->pathfinding->GetLastPath();
		
	iPoint last_tile;
	if(Path->Pop(last_tile)) {
		iPoint closest_center = App->map->MapToWorldCentered(last_tile.x, last_tile.y);


		if (closest_center.DistanceTo(position) < 2) {
			iPoint penultima_tile;
			if (Path->Pop(penultima_tile)) {
				closest_center = App->map->MapToWorldCentered(penultima_tile.x, penultima_tile.y);
			}
		}
		
		position.x += 2 * ((position.x < closest_center.x) ? 1 : -1);
		position.y += 2 * ((position.y < closest_center.y) ? 1 : -1);
		
	}

//	}

	//Draw enemy
	App->map->DrawAnimation("skull_still", "Skull1", position , Ainfo, false);

	return true;
}