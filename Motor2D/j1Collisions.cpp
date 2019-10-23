#include "j1App.h"
#include "j1Collisions.h"
#include "j1Map.h"
#include "j1Render.h"

j1Collisions::j1Collisions() : j1Module(), debug_colliders(true)
{
	name.create("collisions");

}

bool j1Collisions::Init() {

	return true;
};

bool j1Collisions::Awake(pugi::xml_node& config) {


	return true;
};

bool j1Collisions::Start() {

	LoadFromMap();

	return true;
};

bool j1Collisions::PreUpdate() {

	/* Old code for reference

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}*/

	p2List_item<Collider*>* Coll_iterator = colliders.start;
	while (Coll_iterator != nullptr) {

		if (Coll_iterator->data->to_delete == true)
		{
			colliders.del(Coll_iterator);
		}

		Coll_iterator = Coll_iterator->next;
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	Coll_iterator = colliders.start;
	while (Coll_iterator != nullptr) {

		c1 = Coll_iterator->data;
		
		p2List_item<Collider*>* Coll_iterator2 = colliders.start;
		while (Coll_iterator2 != nullptr) {

			c2 = Coll_iterator2->data;

			if (c1 != c2) {
				if (c1->CheckCollision(c2->rect) == true && (c1->type == ObjectType::PLAYER || c2->type == ObjectType::PLAYER))
				{
					if (c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (c2->callback)
						c2->callback->OnCollision(c2, c1);
				}
			}
			Coll_iterator2 = Coll_iterator2->next;
		}

		Coll_iterator = Coll_iterator->next;
	}

	/*
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}
	*/

	return true;
};

bool j1Collisions::Update(float dt) {

	DebugDraw();
	return true;
};

void j1Collisions::DebugDraw() {

	if (debug_colliders == false)
		return;

	Uint8 alpha = 80; 	//MAGIC NUMBER
	p2List_item<Collider*>* Coll_iterator = colliders.start;
	while (Coll_iterator != nullptr) {

		switch (Coll_iterator->data->type)
		{
		case ObjectType::PLATFORM: // white
			App->render->DrawQuad(Coll_iterator->data->rect, 255, 255, 255, alpha);
			break;
		case ObjectType::SOLID: // red
			App->render->DrawQuad(Coll_iterator->data->rect, 255, 0, 0, alpha);
			break;
		case ObjectType::DAMAGE: // green
			App->render->DrawQuad(Coll_iterator->data->rect, 0, 0, 255, alpha);
			break;
		case ObjectType::PLAYER: // blue
			App->render->DrawQuad(Coll_iterator->data->rect, 0, 255, 0, alpha);
			break;
		}

		Coll_iterator = Coll_iterator->next;
	}
}

bool j1Collisions::PostUpdate() {

	return true;
};

bool j1Collisions::CleanUp() {

	return true;
};


Collider* j1Collisions::AddCollider(SDL_Rect rect, ObjectType type, j1Module* callback)
{
	Collider* ret = new Collider;

	ret->callback = callback;
	ret->rect = rect;
	ret->type = type;

	colliders.add(ret);
	
	return ret;
}

//Add Colliders to the list from the map
void j1Collisions::LoadFromMap() {
	p2List_item<MapObjectgroup*>* list_i = App->map->data.objectgroups.start;
	while (list_i != nullptr) {
		for (int i = 0; i < list_i->data->objects_size; i++) {

			AddCollider(*list_i->data->objects[i].box, list_i->data->objects[i].type, nullptr);
		}

		list_i = list_i->next;
	}
}

//  Struct Collider Methods --------------------------------------
bool Collider::CheckCollision(const SDL_Rect& r) const
{

	return ((r.x + r.w > rect.x) && (r.x < rect.x + rect.w) &&
		(r.y + r.h > rect.y) && (r.y < rect.y + rect.h));

}

Collider::Collider(Object object) {
	rect = *object.box;
	type = object.type;
}