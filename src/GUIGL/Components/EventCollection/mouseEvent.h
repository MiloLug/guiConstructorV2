#pragma once

#include "eventElement.h"
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
			class mouseEvent : public eventElement {
			public:
				int x;
				int y;
				MouseButtons button;

				mouseEvent(Elements::Element* topElement, int x, int y, MouseButtons btn) : eventElement(topElement) {
					this->x = x;
					this->y = y;
					this->button = btn;
				}
				mouseEvent() {}
				virtual mouseEvent* copy() {
					mouseEvent* t = new mouseEvent(this->topElement, this->x, this->y, this->button);
					return t;
				}
				virtual ~mouseEvent() {}
			};
		}
	}
}
