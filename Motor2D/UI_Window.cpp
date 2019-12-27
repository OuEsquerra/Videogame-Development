#include "j1Gui.h"
//#include "UI_Window.h"
//#include "UI_Button.h"

UI_Window::UI_Window(int x, int y, bool enabled) : position(x,y) , enabled(enabled)
{

}

void UI_Window::Update()
{
	p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		elementsIt->data->Update();

		elementsIt = elementsIt->next;
	}
}

void UI_Window::Draw()
{
	border->Draw();

	p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		elementsIt->data->Draw();

		elementsIt = elementsIt->next;
	}
}

void UI_Window::addUI(UI* ui,int x, int y)
{
	elements.add(ui);
	ui->position.x = position.x + x;
	ui->position.y = position.y + y;
}

void UI_Window::enable()
{
	//p2List_item<UI*>* elementsIt = elements.start;

	//while (elementsIt != NULL)
	//{
	//	elementsIt->data->Enable();
	//}
	//border->Enable();

	enabled = true;
}

void UI_Window::disable()
{
	/*p2List_item<UI*>* elementsIt = elements.start;

	while (elementsIt != NULL)
	{
		elementsIt->data->Disable();
	}
	border->Disable();*/

	enabled = false;
}