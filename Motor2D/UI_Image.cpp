
#include "j1Gui.h"

UI_Image::UI_Image(int x, int y, bool draggable, SDL_Rect rect,SDL_Texture* image) : UI(x,y,draggable) , rect(rect), image(image)
{

}

void UI_Image::Update()
{

}

void UI_Image::Draw()
{
	App->render->Blit(image, position.x, position.y, &rect, 0.0f);
}