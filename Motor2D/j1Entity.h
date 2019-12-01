
//#include "j1Flying_Enemy.h"

//#include "j1Collisions.h"
#include "p2SString.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

//#include "j1EntityMachine.h"

enum EntityType
{
	PLAYER = 0,
	FLYING_ENEMY,
	GROUND_ENEMY,
	PARTICLE,
	UNKNOWN
};

struct AnimationInfo
{
	int iter;
	p2SString prev_anim_name = "idle";
	float frameCount = 0.0f;
};

//Entity base
class Entity 
{
//VARS
public:
	//Constructor
	iPoint position;
	EntityType type;

	//Vars
	p2SString animation;
	iPoint speed;
	AnimationInfo Ainfo;
	Collider* collider;
	SDL_Rect colliderRect;

//Methods
public:
	Entity(float x, float y , EntityType Type);

	virtual bool Awake();
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual bool Save(pugi::xml_node &);
	virtual bool Load(pugi::xml_node &);
};