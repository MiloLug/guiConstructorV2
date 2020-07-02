#include "StyleSetElement.h"
#include "constants.h"
#include "StyleSetAspectMixer.h"
#include "StyleStorage.h"
#include "../../Elements/Element.h"

namespace GUI {
	namespace Style {
		void StyleSetElement::removeSelf() {
			delete this;
		};
		StyleSetElement::~StyleSetElement() {
			if(this->base != nullptr)
				delete this->base;
		};

		StyleSetElement::StyleSetElement(Elements::Element* el) : StyleSet() {
			this->el = el;
		};

		int StyleSetElement::width() { //get
			return this->_widthSet ? this->_width : this->base->width();
		};
		StyleSetElement* StyleSetElement::width(int t) { //set
			this->_width = t;
			this->_widthSet = true;
			return this;
		};

		int StyleSetElement::height() { //get
			return this->_heightSet ? this->_height : this->base->height();
		};
		StyleSetElement* StyleSetElement::height(int t) { //set
			this->_height = t;
			this->_heightSet = true;
			return this;
		};

		int StyleSetElement::left() { //get
			switch (this->position()) {
			case Parameters::absolute:
				return this->_leftSet ? this->_left : this->base->left();
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_leftSet ? this->_left : this->base->left();
				}
				else {
					return (this->_leftSet ? this->_left : this->base->left()) + this->el->parent()->style->left();
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::left(int t) { //set
			this->_left = t;
			this->_leftSet = true;
			return this;
		};

		int StyleSetElement::top() { //get
			switch (this->position()) {
			case Parameters::absolute:
				return this->_topSet ? this->_top : this->base->top();
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_topSet ? this->_top : this->base->top();
				}
				else {
					return (this->_topSet ? this->_top : this->base->top()) + this->el->parent()->style->top();
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::top(int t) { //set
			this->_top = t;
			this->_topSet = true;
			return this;
		};

		int StyleSetElement::zIndex() { //get
			switch (this->position()) {
			case Parameters::absolute:
				return this->_zIndexSet ? this->_zIndex : this->base->zIndex();
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_zIndexSet ? this->_zIndex : this->base->zIndex();
				}
				else {
					return 1 + (this->_zIndexSet ? this->_zIndex : this->base->zIndex()) + this->el->parent()->style->zIndex();
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::zIndex(int t) { //set
			this->_zIndex = t;
			this->_zIndexSet = true;
			return this;
		};

		Parameters StyleSetElement::position() { //get
			return this->_positionSet ? this->_position : this->base->position();
		};
		StyleSetElement* StyleSetElement::position(Parameters t) { //set
			this->_position = t;
			this->_positionSet = true;
			return this;
		};


		StyleSetElement* StyleSetElement::setBase(StyleSet* set) {
			if (this->base != nullptr)
				delete this->base;
			this->base = set;
			return this;
		};
	}
}