#include <iostream>
#include <string>
#include <GUIGL/Elements/Elements.h>
#include <Math.h>
#include "GUIGL/Components/Event/Emitter.h"
#include "GUIGL/Components/EventCollection/classNameChange.h"
#include <mutex>
#include <GUIGL/Components/Style/StyleStorage.h>

using namespace GUI;
using namespace GUI::Elements;
using namespace std;

mutex m;

int main() {

	Event::init(8);

	Style::StylesStorage::set("gg", GUI::Style::States::plain)
		->height(20)
		->width(30);
	Style::StylesStorage::set("kek", GUI::Style::States::plain)
		->height(40)
		->left(10);


	Window* kek = new Window;

	Element* elem = new Element;

	kek->addElement(elem);

	/*elem->on("classNameChange", [](Event::DataPack* data) {
		Event::EventCollection::classNameChange* ev = (Event::EventCollection::classNameChange*)data;
		string joined = "";

		for (int i = 0, len = ev->newNames.size(); i < len; i++) {
			joined += "." + ev->newNames[i].src;
		}
		m.lock();
		cout << joined << endl;
		m.unlock();
	});*/

	elem->className->add("gg");

	std::cout << "width: " << elem->style->width() << std::endl;
	std::cout << "height: " << elem->style->height() << std::endl;
	std::cout << "left: " << elem->style->left() << std::endl;
	std::cout << "======================" << std::endl;

	elem->className->add("kek");

	std::cout << "width: " << elem->style->width() << std::endl;
	std::cout << "height: " << elem->style->height() << std::endl;
	std::cout << "left: " << elem->style->left() << std::endl;
	std::cout << "======================" << std::endl;

	elem->className->add("lol");
	elem->className->add("ggwp");

	while (1) {
		string exq = "";
		cin >> exq;
		if (exq == "exit") {
			Event::terminate();
			break;
		}
	}

	Event::wait();
	return 0;
}