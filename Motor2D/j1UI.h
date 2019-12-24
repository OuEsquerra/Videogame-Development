




enum class UI_Type
{
	TEXT = 0,
	IMAGE,
	BUTTON,
	UNKNOWN = 3
};


class UI
{

//Vars
public:
	
	iPoint position;

	bool draggable;

	bool enabled;

	bool active;

//Methods
public:

	UI(int x, float y,bool active, bool draggable);

	virtual void Update();

	virtual void Draw();

	bool IsEnabled();

	void Enable();

	void Disable();

private:



};