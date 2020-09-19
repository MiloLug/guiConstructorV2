#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseMove : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseMove(Elements::Element* topElement, int x, int y) : mouseEvent(topElement, x, y, MouseButtons::left) {}
				mouseMove() {}
				virtual mouseMove* copy() {
					mouseMove* t = new mouseMove(this->topElement, this->x, this->y);
					return t;
				}
				virtual ~mouseMove() {}
			};
		}
	}
}