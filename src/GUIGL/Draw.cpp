#include "Draw.h"
#include "glall.h"
#include "Elements/ElementsStore.h"
#include <algorithm>
#include "GLFW/SysWindow.h"
#include <iostream>

#include "guigl.h"

namespace GUI {
	Draw::windowsMap_t Draw::list;
	bool Draw::allowDraw = true;
	std::stack<elemId_t> Draw::toDraw;

	inline void initGlew() {
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			throw std::runtime_error("GUIGL: GLEW initialization failed");
		}
	}

	bool Draw::canWindowDraw(elemId_t wid) {
		Elements::Window* window = (Elements::Window*)Elements::ElementsStore::getElement(wid, wid);
		return window != nullptr 
			&& window->shown
			&& !window->sysWindow->shouldClose();
	}

	void Draw::removeWindowMap(elemId_t wid) {
		Draw::windowsMap_t::const_iterator witer = Draw::list.find(wid);
		if (witer != Draw::list.end()) {
			for (const Draw::zIndexesPair_t &ztmp : *witer->second) {
				delete ztmp.second;
			};
			delete witer->second;
			Draw::list.erase(wid);
		}
	};

	void Draw::terminate() {
		for (const Draw::windowsPair_t &window : Draw::list) {
			Draw::removeWindowMap(window.first);
		}
	}

	void Draw::review() {
		std::stack<elemId_t> wids;
		Draw::zIndexesMap_t* vtmp;
		std::vector<Elements::Element*>* elemsDraw;
		Draw::zIndexesMap_t::const_iterator ziter;
		int currentZ;
		for (const Elements::ElementsStore::windowsPair_t& tmp : Elements::ElementsStore::list) {
			Elements::Window* window = (Elements::Window*)tmp.second->operator[](tmp.first);

			if (window->__reviewZ) {
				Draw::removeWindowMap(window->id);
				vtmp = new Draw::zIndexesMap_t;
				Draw::list[window->id] = vtmp;
				for (const Elements::ElementsStore::elementsPair_t &etmp : *tmp.second) {
					currentZ = etmp.second->style->zIndex();
					ziter = vtmp->find(currentZ);
					if (ziter == vtmp->end()) {
						elemsDraw = new std::vector<Elements::Element*>;
						vtmp->operator[](currentZ) = elemsDraw;
					}
					else
						elemsDraw = ziter->second;
					elemsDraw->push_back(etmp.second);
				}
			}

			if (window->__redraw || window->__reviewZ)
				Draw::toDraw.push(window->id);
			window->__redraw = false;
			window->__reviewZ = false;
		}
	}

	void Draw::draw() {
		if (!Draw::allowDraw)
			return;
		Draw::allowDraw = false;

		Draw::review();
		
		Draw::zIndexesMap_t* window;
		elemId_t tmpid;
		Elements::Window* w;

		while (!Draw::toDraw.empty()) {
			tmpid = Draw::toDraw.top();
			Draw::toDraw.pop();

			w = (Elements::Window*)Elements::ElementsStore::getElement(tmpid, tmpid);
			if (w == nullptr || w->sysWindow->shouldClose()) {
				Draw::removeWindowMap(tmpid);
				continue;
			}
			if (!w->shown)
				continue;
			w->sysWindow->makeContextCurrent();
			initGlew();
			glViewport(0,0, w->style->_width, w->style->_height);

			window = Draw::list[tmpid];

			for (const zIndexesPair_t& ztmp : *window) {
				for (Elements::Element* etmp : *ztmp.second) {
					etmp->__drawBase(w->style->_width, w->style->_height);
				}
			}

			w->sysWindow->swapBuffers();
		}
		Draw::allowDraw = true;
	}
	
}