#ifndef __j1ENTITYMACHINE_H__
#define __j1ENTITYMACHINE_H__

#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

#include "j1Entity.h"
//#include "j1Flying_Enemy.h"


//class Entity;

//enum EntityType;

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

	bool Awake(pugi::xml_node&);

	Entity* CreateEntity(float x, float y, SDL_Rect* Rect, EntityType Type);
	
	void DeleteEntity(Entity* entity);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();


private:

//VARIABLES
public:

	//Flying_Enemy* flying_enemy = nullptr;

	p2List<Entity*> entity_list;

private:
};





#endif //__j1ENTITYMACHINE_H__