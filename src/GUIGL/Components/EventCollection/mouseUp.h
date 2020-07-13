#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseUp : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseUp(int x, int y, MouseButtons btn) : mouseEvent(x, y, btn) {}
				mouseUp() {}
				virtual mouseUp* copy() {
					mouseUp* t = new mouseUp(this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseUp() {}
			};
		}
	}
}