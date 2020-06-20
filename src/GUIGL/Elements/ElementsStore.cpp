#include "ElementsStore.h"
#include <stack>

namespace GUI {
	namespace Elements {
		ElementsStore::windowsMap_t ElementsStore::list;

		Element* ElementsStore::getElement(elemId_t wid, elemId_t eid) {
			ElementsStore::windowsMap_t::const_iterator witer = ElementsStore::list.find(wid);
			if (witer != ElementsStore::list.end()) {
				ElementsStore::elementsMap_t::const_iterator eiter = witer->second->find(eid);
				if (eiter != witer->second->end()) {
					return eiter->second;
				}
			}
			return nullptr;
		}

		void ElementsStore::removeElement(elemId_t wid, elemId_t eid) {
			if (eid == wid)
				return;

			Element* tmp = ElementsStore::getElement(wid, eid);
			if (tmp != nullptr) {
				tmp->removeSelf();
				ElementsStore::list[wid]->erase(eid);
				Event::removeElement(wid, eid);
			}
		};

		void ElementsStore::removeWindow(elemId_t wid) {
			Window* tmp = (Window*)ElementsStore::getElement(wid, wid);
			if (tmp != nullptr) {
				tmp->removeSelf();
				delete ElementsStore::list[wid];
				ElementsStore::list.erase(wid);
				Event::removeWindow(wid);
			}
		}

		void ElementsStore::terminate() {
			while (ElementsStore::list.size())
				ElementsStore::removeWindow(ElementsStore::list.begin()->first);
		}

		void ElementsStore::addElement(Element* elem) {
			ElementsStore::windowsMap_t::const_iterator witer = ElementsStore::list.find(elem->parentWindow);
			if (witer != ElementsStore::list.end()) {
				if (witer->second->find(elem->id) == witer->second->end()) {
					witer->second->operator[](elem->id) = elem;
				}
			}
		}

		void ElementsStore::addWindow(Window* window) {
			ElementsStore::windowsMap_t::const_iterator witer = ElementsStore::list.find(window->id);
			if (witer == ElementsStore::list.end()) {
				ElementsStore::list[window->id] = new ElementsStore::elementsMap_t;
				window->parentWindow = window->id;
				ElementsStore::addElement(window);
			}
		}

		void ElementsStore::removeClosed() {
			std::stack<elemId_t> wids;
			for (const ElementsStore::windowsPair_t& tmp : ElementsStore::list) {
				Window* window = (Window*)tmp.second->operator[](tmp.first);
				if (window->sysWindow->shouldClose())
					wids.push(tmp.first);
				/*else
					if (window->update) {
						window->height = window->newHeight;
						window->width = window->newWidth;
						window->draw();
						window->update = 0;
					}*/
			}
			while (!wids.empty()) {
				ElementsStore::removeWindow(wids.top());
				wids.pop();
			}
		}
	}
}