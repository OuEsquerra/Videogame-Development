#ifndef __j1ENTITYMACHINE_H__
#define __j1ENTITYMACHINE_H__

#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"


#include "j1Entity.h"
#include "j1Flying_Enemy.h"
#include "j1Player.h"
#include "j1Ground_Enemy.h"


//Machine class
class j1EntityMachine : public j1Module {
//METHODS
public:

	j1EntityMachine();

	// Destructor
	//virtual ~j1EntityMachine();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	bool Init();

	bool Awake(pugi::xml_node& config);

	Entity* CreateEntity(float x, float y, EntityType Type);
	
	void DeleteEntity(Entity* entity);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* A, Collider* B);


private:

//VARIABLES
public:

	pugi::xml_node conf;

	p2List<Entity*> entity_list;

	j1Player* player = nullptr;

	Flying_Enemy* skull = nullptr;

	Ground_Enemy* skeleton = nullptr;

	Ground_Enemy* skeleton2 = nullptr;

private:
};





#endif //__j1ENTITYMACHINE_H__