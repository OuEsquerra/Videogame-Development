#ifndef __j1ENTITYMACHINE_H__
#define __j1ENTITYMACHINE_H__

#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"


enum EntityType 
{
	PLAYER = 0,
	FLYING_ENEMY,
	GROUND_ENEMY,
	PARTICLE,
	UNKNOWN
};

class Entity {
		//SDL_Rect rect;
		//SDL_Texture* texture;
		fPoint speed;
		fPoint acceleration;
		EntityType type;

};

class Particle : public Entity {


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

	//Entity* CreateEntity(SDL_Rect* Rect, SDL_Texture* Tex, EntityType Type);
	

	bool Update(float dt);

	bool CleanUp();


private:

//VARIABLES
public:
private:
};





#endif //__j1ENTITYMACHINE_H__