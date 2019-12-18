#include "j1Module.h"



class j1Main_Menu : public j1Module
{
public:

	j1Main_Menu();

	~j1Main_Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();


};
