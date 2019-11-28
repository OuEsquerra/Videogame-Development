
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Map.h"

//#include "j1Flying_Enemy.h"
#include "j1EntityMachine.h"
//#include "j1Entity.h"

bool j1EntityMachine::Save(pugi::xml_node& conf) const {
	return true;
};
bool j1EntityMachine::Load(pugi::xml_node& conf) {
	return true;
};

j1EntityMachine::j1EntityMachine() {
	name.create("entities");
};

bool j1EntityMachine::Start()
{
	return true;
};

bool j1EntityMachine::Init()
{
	return true;
};

bool  j1EntityMachine::Awake(pugi::xml_node&)
{
	p2List_item<Entity*>* entityIter = entity_list.start;

	while (entityIter != NULL)
	{
		//entityIter->data->Awake();

		entityIter = entityIter->next;
	}

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
Entity* j1EntityMachine::CreateEntity(float x, float y, SDL_Rect* Rect, EntityType Type) {

	static_assert(EntityType::UNKNOWN == 4, " Something broke :( ");

	Entity* ret = nullptr;

	switch (Type) {
	case PLAYER:

		//ret = new Player(x, y, Rect, Type); //Struct Player es igual

		break;

	case PARTICLE:
		//ret = new Particle(x,y,Rect,Type);
		break;

	case FLYING_ENEMY:

		/*ret = new Flying_Enemy(x, y, Rect, Type);

		if (ret != nullptr)
		{
			entity_list.add(ret);
		}*/

		//flying_enemy = (Flying_Enemy*)ret;

		break;

	case GROUND_ENEMY:
		//ret = new Enemy_ground(x, y, Rect, Type);
		break;
	}

	//entity_list->add(ret);
	return ret;
};


// Destroy an Entity and remove it from the list -----------------------------------------------------
void j1EntityMachine::DeleteEntity(Entity* entity) {

	delete entity->rect;

	entity_list.del(entity_list.At(entity_list.find(entity)));
}