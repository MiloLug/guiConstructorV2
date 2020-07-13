#pragma once
#include "mouseEvent.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class mouseMove : public mouseEvent {
			public:
				static elemIdNum_t eventId;

				mouseMove(int x, int y) : mouseEvent(x, y, MouseButtons::left) {}
				mouseMove() {}
				virtual mouseMove* copy() {
					mouseMove* t = new mouseMove(this->x, this->y);
					return t;
				}
				virtual ~mouseMove() {}
			};
		}
	}
}