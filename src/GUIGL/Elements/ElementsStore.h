#pragma once
#ifndef __ELEMENTS_ELEMENTSSTORE

#define __ELEMENTS_ELEMENTSSTORE

#include "../common.h"
#include <map>
#include <string>
#include "Window.h"
#include "Element.h"
namespace GUI {
	namespace Elements {
		class ElementsStore
		{
		public:
			typedef std::map<const elemId_t, Element*> elementsMap_t;
			typedef std::pair<const elemId_t, Element*> elementsPair_t;
			typedef std::map<const elemId_t, elementsMap_t*> windowsMap_t;
			typedef std::pair<const elemId_t, elementsMap_t*> windowsPair_t;

			static windowsMap_t list;

			static Element* getElement(elemId_t wid, elemId_t eid);

			static void removeElement(elemId_t wid, elemId_t eid);
			static void removeWindow(elemId_t wid);
			static void terminate();

			static void addElement(Element* elem);
			static void addWindow(Window* window);

			static void removeClosed();
		};
	}
}
#endif
