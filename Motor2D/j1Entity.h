//#include "j1Flying_Enemy.h"
#include "p2SString.h"

//#include "j1EntityMachine.h"

enum EntityType
{
	PLAYER = 0,
	FLYING_ENEMY,
	GROUND_ENEMY,
	PARTICLE,
	UNKNOWN
};

//Entity base
class Entity 
{
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