#include "Style.h"
#include "ElementsStore.h"
#include "Element.h"

namespace GUI {
	namespace Elements {
		std::map<std::string, short int> Style::_position_keys = {
			{"absolute", STYLE_POSITION_ABSOLUTE},
			{"relative", STYLE_POSITION_RELATIVE}
		};
		std::map<short int, std::string> Style::_position_values = {
			{STYLE_POSITION_ABSOLUTE, "absolute"},
			{STYLE_POSITION_RELATIVE, "relative"}
		};

		Style::Style(Element* elem) {
			this->element = elem;
		}

		short int Style::position() { //get
			return this->_position;
		}
		Style* Style::position(short int position) { //set
			if (this->_position == position)
				return this;
			this->_position = position;
			this->element->windowReviewZ();
			return this;
		}
		Style* Style::position(std::string position) { //set
			short int pos = Style::_position_keys[position];
			if (this->_position == pos)
				return this;
			this->_position = pos;
			this->element->windowReviewZ();
			return this;
		}

		int Style::zIndex() { //get
			int z = this->_zIndex;
			Element* tmp = this->element;
			while (
(tmp->style->__customZ ? tmp->style->_position != STYLE_POSITION_ABSOLUTE : true)
&& tmp->parent && (tmp = ElementsStore::getElement(tmp->parentWindow, tmp->parent),
					tmp != nullptr)) {
				z += tmp->style->_zIndex + 1;
			}
			return z;
		}

		Style* Style::zIndex(int zIndex) { //set
			this->__customZ = true;
			if (this->_zIndex == zIndex)
				return this;
			this->_zIndex = zIndex;
			this->element->windowReviewZ();
			return this;
		}

		float Style::width() { //get
			return this->_width;
		}
		Style* Style::width(float width) { //set
			if (this->_width == width)
				return this;
			this->_width = width;
			this->element->windowRedraw();
			return this;
		}

		float Style::height() { //get
			return this->_height;
		}
		Style* Style::height(float height) { //set
			if (this->_height == height)
				return this;
			this->_height = height;
			this->element->windowRedraw();
			return this;
		}

		float Style::left() { //get
			float l = this->_left;
			Element* tmp = this->element;
			while (tmp->style->_position != STYLE_POSITION_ABSOLUTE
				&& tmp->parent && (tmp = ElementsStore::getElement(tmp->parentWindow, tmp->parent),
					tmp != nullptr)) {
				l += tmp->style->_left + tmp->style->_padding;
			}
			return l;
		}
		Style* Style::left(float left) { //set
			if (this->_left == left)
				return this;
			this->_left = left;
			this->element->windowRedraw();
			return this;
		}

		float Style::top() { //get
			float t = this->_top;
			Element* tmp = this->element;
			while (tmp->style->_position != STYLE_POSITION_ABSOLUTE
				&& tmp->parent && (tmp = ElementsStore::getElement(tmp->parentWindow, tmp->parent),
					tmp != nullptr)) {
				t += tmp->style->_top + tmp->style->_padding;
			}
			return t;
		}
		Style* Style::top(float top) { //set
			if (this->_top == top)
				return this;
			this->_top = top;
			this->element->windowRedraw();
			return this;
		}

		float Style::padding() { //get
			return this->_padding;
		}
		Style* Style::padding(float padding) { //set
			if (this->_padding == padding)
				return this;
			this->_padding = padding;
			this->element->windowRedraw();
			return this;
		}

		std::array<float, 4> Style::background() { //get
			return std::array<float, 4>{
				this->_background[0] * 255,
				this->_background[1] * 255,
				this->_background[2] * 255,
				this->_background[3]
			};
		}
		Style* Style::background(float r, float g, float b, float a) { //set
			r = r / 255;
			g = g / 255;
			b = b / 255;
			if ((this->_background[0] - r
				+ this->_background[1] - g
				+ this->_background[2] - b
				+ this->_background[3] - a) == 0)
				return this;

			this->_background[0] = r;
			this->_background[1] = g;
			this->_background[2] = b;
			this->_background[3] = a;
			this->element->windowRedraw();
			return this;
		}

		std::array<float, 8> Style::shadow() { //get
			return std::array<float, 8>{
				this->_shadow[0],
				this->_shadow[1],
				this->_shadow[2],
				this->_shadow[3],
				this->_shadow[4] * 255,
				this->_shadow[5] * 255,
				this->_shadow[6] * 255,
				this->_shadow[7],
			};
		}
		Style* Style::shadow(float xOffset, float yOffset, float blurRadius, float spread, float r, float g, float b, float a) { //set
			r = r / 255;
			g = g / 255;
			b = b / 255;
			if ((this->_shadow[0] - xOffset
				+ this->_shadow[1] - yOffset
				+ this->_shadow[2] - blurRadius
				+ this->_shadow[3] - spread
				+ this->_shadow[4] - r
				+ this->_shadow[5] - g
				+ this->_shadow[6] - b
				+ this->_shadow[7] - a) == 0)
				return this;

			this->_shadow[0] = xOffset;
			this->_shadow[1] = yOffset;
			this->_shadow[2] = blurRadius;
			this->_shadow[3] = spread;
			this->_shadow[4] = r;
			this->_shadow[5] = g;
			this->_shadow[6] = b;
			this->_shadow[7] = a;
			this->element->windowRedraw();
			return this;
		}
	}
}