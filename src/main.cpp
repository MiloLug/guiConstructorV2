#include <iostream>
#include <GUIGL/guigl.h>
#include <GUIGL/Event.h>
#include <string>

#include <Math.h>

using namespace GUI;
using namespace GUI::Elements;

int main() {
	try{
		GUI::init();
	}catch (std::runtime_error e) {
		std::cout << "Runtime Error: " << e.what() << std::endl;
	}
	

	Window* win = new Window(strHash("lol kek"));
	Window* win2 = new Window(strHash("lol kek2"));

	win->style->width(800);
	win->style->height(600);
	win->title("lol kek win");
	win->style->background(255, 0, 255, 1);

	win2->style->width(400);
	win2->style->height(600);
	win2->title("lol kek win 2");
	win2->style->background(255, 50, 255, 1);

	ElementsStore::addWindow(win);
	ElementsStore::addWindow(win2);


	Button* btn1 = new Button(strHash("lolbtn1"));
	win->addElement(btn1);
	btn1->style->width(100);
	btn1->style->height(50);

	Button* btn2 = new Button(strHash("lolbtn2"));
	win->addElement(btn2);
	btn2->style->width(100);
	btn2->style->height(50);
	btn2->style->top(80);

	bool dragStart = false;
	elemId_t moveId;
	int xdist = 0;
	int ydist = 0;
	std::function<void(Element*)> fn = [&win, &dragStart, &xdist, &ydist, &moveId](Element* el) {
		el->on("mouseDown", [&dragStart, &xdist, &ydist, el, &moveId](Event::baseEvent* e) {
			dragStart = true;
			Event::mouseButtonEvent* ev = (Event::mouseButtonEvent*)e;

			xdist = ev->X - el->style->left();
			ydist = ev->Y - el->style->top();
			moveId = e->topElelemt;
		});

		win->on("mouseMove", [&dragStart, &xdist, &ydist, el, &moveId](Event::baseEvent* e) {
			if (dragStart && el->id == moveId) {
				Event::mouseMoveEvent* ev = (Event::mouseMoveEvent*)e;

				el->style->left(ev->X - xdist);
				el->style->top(ev->Y - ydist);
			}
		});

		win->on("mouseUp", [&dragStart](Event::baseEvent* e) {
			dragStart = false;
		});
	};

	fn(btn1);
	fn(btn2);
	/*win->on("mouseDown", [&dragStart](GUI::Event::baseEvent* e) {
		dragStart = true;
		GUI::Event::mouseButtonEvent* ev = (GUI::Event::mouseButtonEvent*)e;
		std::cout << "drag start: " << ev->X << ":" << ev->Y << std::endl;
	});
	
	win->on("mouseMove", [&dragStart, &win](GUI::Event::baseEvent* e) {
		if (dragStart) {
			GUI::Event::mouseMoveEvent* ev = (GUI::Event::mouseMoveEvent*)e;
			std::cout << "dragging: " << ev->X << ":" << ev->Y << std::endl;
			
		}
	});
	win->on("mouseUp", [&dragStart](GUI::Event::baseEvent* e) {
		dragStart = false;
		GUI::Event::mouseButtonEvent* ev = (GUI::Event::mouseButtonEvent*)e;
		std::cout << "drag end: " << ev->X << ":" << ev->Y << std::endl;
	});*/


	/*Window* winp = new Window(GUI::strHash("_lol"));
	winp->style->width(300);
	winp->style->height(300);
	winp->title("PIDARAS");
	winp->style->background(255, 0, 255, 1);

	ElementsStore::addWindow(winp);

	GUI::Event::defaultELFn sonof = [&id, &sonof](GUI::Event::baseEvent* e) {
		id++;
		std::cout << id << std::endl;
		Window* tmp = new Window(GUI::strHash(("lol" + std::to_string(id)).c_str()));
		ElementsStore::addWindow(tmp);

		Element* p = ElementsStore::getElement(e->window, e->element);

		tmp->on("mouseDown", sonof);
		std::string tt = "SON OF " + p->title();

		tmp->style->width(p->style->width() + 50.f);
		tmp->style->height(50);
		tmp->title(tt);
	};
	winp->on("mouseDown", sonof);*/


	GUI::runLoop();


	GUI::terminate();
	return 0;
}