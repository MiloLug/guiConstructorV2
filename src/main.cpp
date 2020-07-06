#include <iostream>
#include <string>
#include <GUIGL/Elements/Elements.h>
#include <Math.h>
#include "GUIGL/Components/Event/Emitter.h"
#include "GUIGL/Components/EventCollection/classNameChange.h"
#include <mutex>

using namespace GUI;
using namespace GUI::Elements;
using namespace std;

mutex m;

int main() {

	Event::init(8);


	Window* kek = new Window;

	Element* elem = new Element;

	kek->addElement(elem);

	elem->on("classNameChange", [](Event::DataPack* data) {
		Event::EventCollection::classNameChange* ev = (Event::EventCollection::classNameChange*)data;
		string joined = "";

		for (int i = 0, len = ev->newNames.size(); i < len; i++) {
			joined += "." + ev->newNames[i].src;
		}
		m.lock();
		cout << joined << endl;
		m.unlock();
	});

	elem->className->push("gg");
	elem->className->push("kek");
	elem->className->push("lol");
	elem->className->push("ggwp");

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