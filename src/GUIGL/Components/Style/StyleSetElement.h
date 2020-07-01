#pragma once
#include "StyleSet.h"

namespace GUI {
	namespace Elements {
		class Element;
	}
	namespace Style {
		class StyleSetElement : public StyleSet{
		public:
			virtual void removeSelf();
			virtual ~StyleSetElement();

			Elements::Element* el = nullptr;
			StyleSet *base = nullptr;

			StyleSetElement(Elements::Element *el);

			virtual int width();
			virtual StyleSetElement* width(int t);

			virtual int height();
			virtual StyleSetElement* height(int t);

			virtual int left();
			virtual StyleSetElement* left(int t);

			virtual int top();
			virtual StyleSetElement* top(int t);

			virtual int zIndex();
			virtual StyleSetElement* zIndex(int t);

			virtual char position();
			virtual StyleSetElement* position(char t);

			StyleSetElement* setBase(StyleSet *set);
		};
	}
}

