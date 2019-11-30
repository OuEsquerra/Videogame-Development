#include "j1EntityMachine.h"

//Flying_Enemy Entity
class Ground_Enemy : public Entity {

	//Methods
public:
	Ground_Enemy(float x, float y, SDL_Rect* rect, EntityType Type);

	bool Awake(pugi::xml_node &);

	bool Start();

	bool Update(float dt);

};