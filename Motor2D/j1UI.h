



enum UI_Type
{
	TEXT = 0,
	IMAGE,
	BUTTON,
	DEFAULT = 3
};


class UI
{

//Vars
public:
	
	iPoint position;

	bool draggable;

//Methods
public:

	UI(int x, float y,bool draggable);

	virtual void Update();

	virtual void Draw();

private:



};