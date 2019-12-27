#pragma once

#include "j1EntityMachine.h"


//Coin Entity
class Coin : public Entity {
	//variables
public:
	fPoint goal;


	//Methods
public:
	Coin(float x, float y, EntityType Type);

	bool Awake(pugi::xml_node &);

	bool Start();

	bool Update(float dt);

	void pathfind();

	bool Save(pugi::xml_node & node) const;
	bool Load(pugi::xml_node & node);
};