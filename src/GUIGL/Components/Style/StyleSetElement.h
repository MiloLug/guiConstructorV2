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

			/*virtual int width(bool* interactState);
			virtual int width();
			virtual StyleSetElement* width(int t);

			virtual int height(bool* interactState);
			virtual int height();
			virtual StyleSetElement* height(int t);

			virtual int left(bool* interactState);
			virtual int left();
			virtual StyleSetElement* left(int t);

			virtual int top(bool* interactState);
			virtual int top();
			virtual StyleSetElement* top(int t);

			virtual int zIndex(bool* interactState);
			virtual int zIndex();
			virtual StyleSetElement* zIndex(int t);*/

			StyleSetElement* setBase(StyleSet *set);
		};
	}
}

