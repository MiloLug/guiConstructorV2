#include <iostream>
#include <string>
#include <GUIGL/Elements/Elements.h>
#include "GUIGL/Components/EventCollection/classNameChange.h"
#include <mutex>
#include "GUIGL/Components/Style/StyleStorage.h"
#include "GUIGL/Elements/Window.h"
#include "GUIGL/Components/EventCollection/mouseMove.h"
#include "GUIGL/guigl.h"


using namespace GUI;
using namespace GUI::Elements;
using namespace std;

mutex m;

int main() {
	GUI::init(8);

	Style::StylesStorage::set("mainWindow", Style::States::plain)
		->width(300)
		->height(800);
	Style::StylesStorage::set("mainWindow", Style::States::press)
		->width(500)
		->height(800);

	Window* w = new Window(800, 600, "kek");
	Window* w2 = new Window(800, 600, "kek22");

	w->className->add("mainWindow");
	w2->className->add("mainWindow");

	w->style->press(true);

	std::cout<<Style::StylesStorage::set("mainWindow", Style::States::press)->_widthSet;


	//w->style->press(true);

	Element* gg = new Element;
	gg->style
		->width(150)
		->height(400)
		->top(200)
		->left(75);

	w->addElement(gg);

	w->on("mouseMove", [&w](Event::DataPack* d) {
		Event::EventCollection::mouseMove* t = (Event::EventCollection::mouseMove*)d;
		m.lock();
		cout << "X: " << t->x << " Y: " << t->y << endl;
		m.unlock();
	});

	gg->on("mouseDown", [&w](Event::DataPack* d) {
		m.lock();
		cout << "MOUSEDOWN GG" << endl;
		m.unlock();
	});

	GUI::terminate();
	
	return 0;
}