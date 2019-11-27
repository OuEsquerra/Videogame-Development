#ifndef __j1ENTITYMACHINE_H__
#define __j1ENTITYMACHINE_H__

#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "j1Flying_Enemy.h"


enum EntityType 
{
	PLAYER = 0,
	ENEMY,
	FLYING_ENEMY,
	GROUND_ENEMY,
	PARTICLE,
	UNKNOWN
};

//Entity base
class Entity {
//VARS
public:
	//Constructor
	SDL_Rect* rect;
	fPoint position;
	EntityType type;

	//Vars
	p2SString animation;
	fPoint speed;

//Methods
public:
	Entity(float x, float y , SDL_Rect* rect, EntityType Type);

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual bool Save(pugi::xml_node &);
	virtual bool Load(pugi::xml_node &);
	

};

//Flying_Enemy Entity
class Flying_Enemy : public Entity {

//Methods
public:
	Flying_Enemy(float x, float y, SDL_Rect* rect, EntityType Type);

	bool Awake(pugi::xml_node &);

	bool Start();

	bool Update(float dt);

};

//class Particle : public Entity {
//public:
//	
//	Particle(float x, float y,SDL_Rect* rect, EntityType Type) : Entity(x, y, rect, Type) {};
//};

//class Enemy : public Entity {
//public:
//	Enemy(float x, float y, SDL_Rect* rect, EntityType Type) : Entity(x,y,rect,Type) {};
//};

//class Enemy_ground : public Enemy {
//public:
//	Enemy_ground(float x, float y, SDL_Rect* rect, EntityType Type) : Enemy(x,y,rect,Type) {};
//};


//Machine class
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

	void CreateEntity(float x, float y, SDL_Rect* Rect, EntityType Type);
	
	void DeleteEntity(Entity* entity);

	bool Start();

	bool Update(float dt);

	bool CleanUp();


private:

//VARIABLES
public:


	Flying_Enemy* flying_enemy = nullptr;


	p2List<Entity*> entity_list;

private:
};





#endif //__j1ENTITYMACHINE_H__