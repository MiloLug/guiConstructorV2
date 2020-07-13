#pragma once
#include "../common.h"
#include <functional>
#include "../Components/Container.h"
#include "Element.h"

namespace GUI {
	namespace Elements {
		class ElementContainer : public Container, public Element {
		public:
			//std::mutex m;
			//base type info =========================
			static const std::type_info* __base_type;
			virtual const std::type_info* __current_type();
			//attributes =========================

			//data =========================
			inline virtual Window* parentWindow();
			inline virtual Element* parentWindow(Window* w);
			inline virtual Element* parentWindowForceMove(Window* w);
			inline virtual Element* parent();
			inline virtual Element* parent(Element* w);
			//constructor =========================
			ElementContainer();
			ElementContainer(const ElementContainer& e) = delete;
			ElementContainer(const ElementContainer* e) = delete;

			//some methods =========================	
			virtual ElementContainer* addElement(Element* elem);
			virtual ElementContainer* removeElement(Element* elem);

			inline virtual ElementContainer* linkElement(Element* elem);
			virtual ElementContainer* unlinkElement(Element* elem);

			virtual ElementContainer* unlinkAll();
			virtual ElementContainer* removeAll();

			virtual void __drawBase(int wwidth, int wheight);


			inline virtual Element* __updateLeft();

			inline virtual Element* __updateTop();

			inline virtual Element* __updateZ();

			inline virtual Element* __updatePos();


			virtual void removeSelf();
			virtual ~ElementContainer();
		};
	}
}
