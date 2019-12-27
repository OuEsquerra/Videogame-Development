
#include "UI_Window.h"
//#include "UI_Button.h"

UI_Window::UI_Window(int x, int y, bool active) : position(x,y) , active(active)
{

}

void UI_Window::Update()
{
	p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		//elementsIt->data->position = position;
	}

}

void UI_Window::addUI(UI* ui)
{
	elements.add(ui);
	ui->position += position;
}

void UI_Window::enable()
{
	p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		elementsIt->data->Enable();
	}
	border->Enable();
}

void UI_Window::disable()
{
	p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		elementsIt->data->Disable();
	}
	border->Disable();
}