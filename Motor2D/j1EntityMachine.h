#ifndef __j1ENTITYMACHINE_H__
#define __j1ENTITYMACHINE_H__

#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"


enum EntityType 
{
	PLAYER = 0,
	ENEMY,
	FLYING_ENEMY,
	GROUND_ENEMY,
	PARTICLE,
	UNKNOWN
};

class Entity {
public:
	SDL_Rect* rect;
	SDL_Texture* texture;
	fPoint speed;
	fPoint acceleration;
	EntityType type;

	p2SString animation;

	Entity(EntityType Type) : type(Type) {}
};

class Particle : public Entity {
public:
	
	Particle() : Entity(PARTICLE) {};

};

//Make it unusable
class Enemy : public Entity {
public:
	Enemy(EntityType Type) : Entity(Type) {};

};

class Enemy_ground : public Enemy {
public:
	Enemy_ground() : Enemy(GROUND_ENEMY) {};
};

class Enemy_aerial : public Enemy {
public:
	Enemy_aerial() : Enemy(FLYING_ENEMY) {};
};

class j1EntityMachine : public j1Module {
//METHODS
public:

	j1EntityMachine();

	// Destructor
	//virtual ~j1EntityMachine();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	//bool Init();

	bool Awake(pugi::xml_node&);

	bool Start();

	Entity* CreateEntity(SDL_Rect* Rect, SDL_Texture* Tex, EntityType Type);
	
	void DeleteEntity(Entity* entity);


	bool Update(float dt);

	bool CleanUp();


private:

//VARIABLES
public:

private:

	p2List<Entity*>* entity_list;
	
};





#endif //__j1ENTITYMACHINE_H__