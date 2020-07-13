#include <iostream>
#include <string>
#include <GUIGL/Elements/Elements.h>
#include <Math.h>
#include "GUIGL/Components/Event/Emitter.h"
#include "GUIGL/Components/EventCollection/classNameChange.h"
#include <mutex>
#include "GUIGL/Components/Style/StyleStorage.h"
#include "GUIGL/Elements/Window.h"
#include <GLFW/glfw3.h>
#include "GUIGL/Components/EventCollection/mouseMove.h"
#include "GUIGL/guigl.h"

using namespace GUI;
using namespace GUI::Elements;
using namespace std;

mutex m;

int main() {
	GUI::init(8);

	Window* w = new Window(800, 600, "kek");
	w->makeContextCurrent();

	w->style
		->width(200)
		->height(600);

	w->on("mouseMove", [&w](Event::DataPack* d) {
		Event::EventCollection::mouseMove* t = (Event::EventCollection::mouseMove*)d;
		m.lock();
		cout << "X: " << t->x << " Y: " << t->y << endl;
		m.unlock();
	});

	GUI::terminate();
	
	return 0;
}