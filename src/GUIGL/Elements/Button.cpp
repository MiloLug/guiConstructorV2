#include "Button.h"
#include "../GL/VAO.h"
#include <iostream>

namespace GUI {
	namespace Elements {
		const std::type_info* Button::__base_type = Element::__base_type;

		Button::Button(elemId_t id, elemId_t parentWindow, elemId_t parent) : Element(id, parentWindow, parent) {
			this->__current_type = Element::__base_type;
			this->Element::__current_type = Element::__base_type;
		}

		void Button::__drawBase(int wwidth, int wheight) {
			VAO vao;
			/*vao.addVBO({
				this->style->left(), this->style->top(), 0,
				this->style->left()+ this->style->width(), this->style->top(), 0,
				this->style->left() + this->style->width()/2, this->style->top()+this->style->height(), 0
			});*/
			float x = 2.f * this->style->left() / wwidth - 1.f;
			float y = 1.f - 2.f * this->style->top() / wheight;
			float w = 2.f * (this->style->left()+ this->style->width()) / wwidth - 1.f;
			float h = 1.f - 2.f * (this->style->top() + this->style->height()) / wheight;
			vao.addVBO({
		x, y, 0,
		w, y, 0,
		w, h, 0,
		x, h, 0
				});
			vao.draw(4);
		}

		void Button::removeSelf() {
			delete this;
		}
		Button::~Button() {}
	}
}