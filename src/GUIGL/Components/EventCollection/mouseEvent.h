#pragma once

#include "../Event/DataPack.h"
#include "../../common.h"
#include <GLFW/glfw3.h>

namespace GUI {
	namespace Event {
		namespace EventCollection {
			enum MouseButtons {
				left = GLFW_MOUSE_BUTTON_LEFT,
				middle = GLFW_MOUSE_BUTTON_MIDDLE,
				right = GLFW_MOUSE_BUTTON_RIGHT
			};
			class mouseEvent : public DataPack {
			public:
				int x;
				int y;
				MouseButtons button;

				mouseEvent(int x, int y, MouseButtons btn) {
					this->x = x;
					this->y = y;
					this->button = btn;
				}
				mouseEvent() {}
				virtual mouseEvent* copy() {
					mouseEvent* t = new mouseEvent(this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseEvent() {}
			};
		}
	}
}
