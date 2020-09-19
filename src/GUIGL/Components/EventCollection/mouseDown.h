#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseDown : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseDown(Elements::Element* topElement, int x, int y, MouseButtons btn) : mouseEvent(topElement, x, y, btn) {}
				mouseDown() {}
				virtual mouseDown* copy() {
					mouseDown* t = new mouseDown(this->topElement, this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseDown() {}
			};
		}
	}
}