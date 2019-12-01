#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1FadeToBlack.h"

#include "BroFiler/Brofiler.h"

#include "j1EntityMachine.h"

j1EntityMachine::j1EntityMachine() {
	name.create("entities");
};

bool j1EntityMachine::Start()
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->Start();

		entityIter = entityIter->next;
	}

	return true;
};

bool j1EntityMachine::Init()
{
	return true;
};

bool  j1EntityMachine::Awake(pugi::xml_node& config)
{
	/*p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->Awake(config);

		entityIter = entityIter->next;
	}*/

	return true;
};

bool j1EntityMachine::PreUpdate()
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->PreUpdate();

		entityIter = entityIter->next;
	}

	return true;
}

bool j1EntityMachine::Update(float dt)
{
	BROFILER_CATEGORY("j1EntityMachine::Update", Profiler::Color::Red);

	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->Update(dt);

		entityIter = entityIter->next;
	}

	return true;
};

bool j1EntityMachine::PostUpdate()
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->PostUpdate();

		entityIter = entityIter->next;
	}

	return true;
}

bool j1EntityMachine::CleanUp() {

	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->CleanUp();

		entityIter = entityIter->next;
	}

	return true;
};

// Create an Entity and add to the list ----------------------------------------------------
Entity* j1EntityMachine::CreateEntity(float x, float y, EntityType Type) {

	static_assert(EntityType::UNKNOWN == 4, " Something broke :( ");

	Entity* ret = nullptr;

	switch (Type) {
	case PLAYER:

		ret = new j1Player(x, y, Type); //Struct Player es igual

		player = (j1Player*)ret;

		if (ret != nullptr)
		{
			entity_list.add(ret);
		}

		ret->Awake();
		ret->Start();

		break;

	case PARTICLE:
		//ret = new Particle(x,y,Rect,Type);
		break;

	case FLYING_ENEMY:

		ret = new Flying_Enemy(x, y, Type);

		if (ret != nullptr)
		{
			entity_list.add(ret);
		}

		

		break;

	case GROUND_ENEMY:

		ret = new Ground_Enemy(x, y, Type);

		if (ret != nullptr)
		{
			entity_list.add(ret);
		}

		

		break;
	}

	

	return ret;
};


// Destroy an Entity and remove it from the list -----------------------------------------------------
void j1EntityMachine::DeleteEntity(Entity* entity) 
{
	entity_list.del(entity_list.At(entity_list.find(entity)));
}

bool j1EntityMachine::Save(pugi::xml_node& conf) const 
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->Save(conf);

		entityIter = entityIter->next;
	}

	return true;
};

bool j1EntityMachine::Load(pugi::xml_node& conf) 
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		entityIter->data->Load(conf);

		entityIter = entityIter->next;
	}

	return true;
};

void j1EntityMachine::OnCollision(Collider* A, Collider* B)
{
	PlayerCollisions(A, B);

	AttackCollisions(A, B);
}

void j1EntityMachine::AttackCollisions(Collider* A, Collider* B)
{
	if (A->type == ObjectType::ATTACK && B->type == ObjectType::ENEMY) {

		DeleteEntity(B->entity);


	}
}

void j1EntityMachine::PlayerCollisions(Collider* A, Collider* B)
{
	if (player->player.godMode) return; //While in God Mode Collisions are disregarded

	if (B->type == ObjectType::PLAYER) {
		Collider temp = *A;
		A = B;
		B = &temp;
	}
	if (A->type != ObjectType::PLAYER) {
		return;
	}

	// ------------ Player Colliding against solids ------------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::SOLID) {

		//from above
		if (player->position.y + A->rect.h > B->rect.y
			&& player->position.y < B->rect.y
			&& A->rect.x < B->rect.x + B->rect.w
			&& A->rect.x + A->rect.w > B->rect.x
			&& player->player.prevposition.y + player->player.boxH <= B->rect.y + 1 //MagicNumber
			&& player->player.justLoaded == false)
		{
			if (player->player.speed.y > 0)
			{
				player->player.speed.y = 0;
			}
			player->position.y = B->rect.y - player->player.collider->rect.h + 1;
			player->player.collider->SetPos(player->position.x + player->player.boxOffset_x, player->position.y);
			player->player.SetGroundState(true);
		}

		//from below
		if (player->player.prevposition.y > (B->rect.y + B->rect.h - 1))
		{
			player->position.y = B->rect.y + B->rect.h;
			player->player.cealing = true;
			player->player.collider->SetPos(player->position.x + player->player.boxOffset_x, player->position.y);
		}

		//from a side
		if (player->position.y + (A->rect.h* 0.1f) < B->rect.y + B->rect.h
			&& player->position.y + (A->rect.h* 0.9f) > B->rect.y)
		{
			player->player.wall = true;
			LOG("Touching WALL");

			if ((A->rect.x + A->rect.w) < (B->rect.x + B->rect.w / 4))
			{ //Player to the left 
				player->position.x = B->rect.x - A->rect.w - player->player.boxOffset_x + 1;

			}
			else if (A->rect.x > (B->rect.x + B->rect.w * 3 / 4))
			{ //Player to the right
				player->position.x = B->rect.x + B->rect.w - player->player.boxOffset_x - 1;
			}
			player->player.collider->SetPos(player->position.x + player->player.boxOffset_x, player->position.y);
		}
	}
	// ------------ Player Colliding against a platform -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::PLATFORM) {

		if (player->player.drop_plat == false) {

			if ((player->player.prevposition.y + player->player.collider->rect.h) < B->rect.y + (B->rect.h / 2.0f) && (player->player.prevposition.y + player->player.collider->rect.h) > B->rect.y && player->player.speed.y >= 0) {//this won't ever happen
				player->position.y = B->rect.y - player->player.collider->rect.h + 1;
				player->player.able_to_jump = false;
				player->player.onPlatform = true;
			}
			else if ((player->position.y >= player->player.prevposition.y) && (player->player.prevposition.y + player->player.collider->rect.h) < B->rect.y && player->player.speed.y >= 0) {
				player->position.y = B->rect.y - player->player.collider->rect.h + 1;
				player->player.SetGroundState(true);
				player->player.able_to_jump = false;
				player->player.onPlatform = true;
			}
		}

	}
	// ------------ Player Colliding against a warp zone -----------------
	if (A->type == ObjectType::PLAYER && B->type == ObjectType::WARP) {
		App->fade->FadeToBlack(B->userdata->Get("MapToLoad").v_string);
	}
}