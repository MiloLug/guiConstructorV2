#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseDown : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseDown(int x, int y, MouseButtons btn) : mouseEvent(x, y, btn) {}
				mouseDown() {}
				virtual mouseDown* copy() {
					mouseDown* t = new mouseDown(this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseDown() {}
			};
		}
	}
}