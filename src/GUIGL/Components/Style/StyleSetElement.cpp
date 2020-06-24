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

		/*int StyleSetElement::width(bool* interactState) {};
		int StyleSetElement::width() {};
		StyleSetElement* StyleSetElement::width(int t) {};

		int StyleSetElement::height(bool* interactState) {};
		int StyleSetElement::height() {};
		StyleSetElement* StyleSetElement::height(int t) {};

		int StyleSetElement::left(bool* interactState) {};
		int StyleSetElement::left() {};
		StyleSetElement* StyleSetElement::left(int t);

		int StyleSetElement::top(bool* interactState) {};
		int StyleSetElement::top() {};
		StyleSetElement* StyleSetElement::top(int t) {};

		int StyleSetElement::zIndex(bool* interactState) {};
		int StyleSetElement::zIndex() {};
		StyleSetElement* StyleSetElement::zIndex(int t) {};*/

		StyleSetElement* StyleSetElement::setBase(StyleSet* set) {
			if (this->base != nullptr)
				delete this->base;
			this->base = set;
			return this;
		};
	}
}