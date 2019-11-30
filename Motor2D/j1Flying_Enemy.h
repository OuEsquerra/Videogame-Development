
#include "j1EntityMachine.h"

//#include "j1Entity.h"

//struct SDL_Rect;

//class Entity;

//enum EntityType;


//Flying_Enemy Entity
class Flying_Enemy : public Entity {
	//variables
public:
	iPoint goal;
	

	//Methods
public:
	Flying_Enemy(float x, float y, SDL_Rect* rect, EntityType Type);

	bool Awake(pugi::xml_node &);

	bool Start();

	bool Update(float dt);


};