#pragma once

#include "../Event/DataPack.h"
#include <vector>
#include "../../common.h"

namespace GUI {
	namespace Elements {
		class Element;
	}
	namespace Event {
		namespace EventCollection {
			class eventElement : public DataPack {
			public:
				Elements::Element* topElement = nullptr;

				eventElement(Elements::Element* topElement) {
					this->topElement = topElement;
				}
				eventElement() {}
				virtual eventElement* copy() {
					eventElement* t = new eventElement(this->topElement);
					return t;
				}
				virtual ~eventElement() {}
			};
		}
	}
}