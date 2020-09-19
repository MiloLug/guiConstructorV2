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
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_widthSet || this->base == nullptr ? this->_width : this->base->width(this->stateMap);
		};

		StyleSetElement* StyleSetElement::width(int t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_width = t;
			this->_widthSet = true;
			this->el->__updateWidth();
			return this;
		};

		int StyleSetElement::height() { //get
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_heightSet || this->base == nullptr ? this->_height : this->base->height(this->stateMap);
		};
		StyleSetElement* StyleSetElement::height(int t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_height = t;
			this->_heightSet = true;
			this->el->__updateHeight();
			return this;
		};

		int StyleSetElement::left() { //get
			std::lock_guard<std::recursive_mutex> g(this->m);
			switch (this->position()) {
			case Parameters::absolute:
				return this->_leftSet || this->base == nullptr ? this->_left : this->base->left(this->stateMap);
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_leftSet || this->base == nullptr ? this->_left : this->base->left(this->stateMap);
				}
				else {
					return (this->_leftSet || this->base == nullptr ? this->_left : this->base->left(this->stateMap)) + (this->el->parent() == nullptr ? 0 : this->el->parent()->style->left());
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::left(int t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_left = t;
			this->_leftSet = true;
			this->el->__updateLeft();
			return this;
		};

		int StyleSetElement::top() { //get
			std::lock_guard<std::recursive_mutex> g(this->m);
			switch (this->position()) {
			case Parameters::absolute:
				return this->_topSet || this->base == nullptr ? this->_top : this->base->top(this->stateMap);
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_topSet || this->base == nullptr ? this->_top : this->base->top(this->stateMap);
				}
				else {
					return (this->_topSet || this->base == nullptr ? this->_top : this->base->top(this->stateMap)) + (this->el->parent() == nullptr ? 0 : this->el->parent()->style->top());
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::top(int t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_top = t;
			this->_topSet = true;
			this->el->__updateTop();
			return this;
		};

		int StyleSetElement::zIndex() { //get
			std::lock_guard<std::recursive_mutex> g(this->m);
			switch (this->position()) {
			case Parameters::absolute:
				return this->_zIndexSet || this->base == nullptr ? this->_zIndex : this->base->zIndex(this->stateMap);
				break;
			case Parameters::relative:
				if (this->el->parent() == nullptr) {
					return this->_zIndexSet || this->base == nullptr ? this->_zIndex : this->base->zIndex(this->stateMap);
				}
				else {
					return 1 + (this->_zIndexSet || this->base == nullptr ? this->_zIndex : this->base->zIndex(this->stateMap)) + (this->el->parent() == nullptr ? 0 : this->el->parent()->style->zIndex());
				}
				break;
			}
		};
		StyleSetElement* StyleSetElement::zIndex(int t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_zIndex = t;
			this->_zIndexSet = true;
			this->el->__updateZ();
			return this;
		};

		Parameters StyleSetElement::position() { //get
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_positionSet || this->base == nullptr ? this->_position : this->base->position(this->stateMap);
		};
		StyleSetElement* StyleSetElement::position(Parameters t) { //set
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_position = t;
			this->_positionSet = true;

			this->el->__updatePos();
			return this;
		};


		StyleSetElement* StyleSetElement::setBase(StyleSetAspectMixer* set) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->base != nullptr)
				delete this->base;
			this->base = set;
			return this;
		};

		StyleSetElement* StyleSetElement::mixAspects(const HashId* begin, const HashId* end, const int size) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->base == nullptr)
				this->base = StylesStorage::aspectMixer(begin, end, size);
			else
				StylesStorage::rebuildAspectMixer((StyleSetAspectMixer*)this->base, begin, end, size);
			this->el->__updatePos();
			return this;
		}

		StyleSetElement* StyleSetElement::hover(bool state) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->stateMap[Style::States::hover-1] = state;
			this->el->__updatePos();
			return this;
		};

		StyleSetElement* StyleSetElement::press(bool state) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->stateMap[Style::States::press-1] = state;
			this->el->__updatePos();
			return this;
		};
	}
}