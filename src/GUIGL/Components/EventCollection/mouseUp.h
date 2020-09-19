#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseUp : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseUp(Elements::Element* topElement, int x, int y, MouseButtons btn) : mouseEvent(topElement, x, y, btn) {}
				mouseUp() {}
				virtual mouseUp* copy() {
					mouseUp* t = new mouseUp(this->topElement, this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseUp() {}
			};
		}
	}
}