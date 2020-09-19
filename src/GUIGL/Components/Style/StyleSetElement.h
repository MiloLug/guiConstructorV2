#pragma once
#include "StyleSet.h"
#include "../../common.h"
#include <mutex>

namespace GUI {
	namespace Elements {
		class Element;
	}
	namespace Style {
		class StyleSetAspectMixer;
		class StyleSetElement : public StyleSet{
		public:
			std::recursive_mutex m;

			virtual void removeSelf();
			virtual ~StyleSetElement();

			Elements::Element* el = nullptr;
			StyleSetAspectMixer *base = nullptr;
			bool stateMap[States::mapSize] = { false };

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

			virtual Parameters position();
			virtual StyleSetElement* position(Parameters t);

			StyleSetElement* setBase(StyleSetAspectMixer *set);

			StyleSetElement* mixAspects(const HashId* begin, const HashId* end, const int size);

			StyleSetElement* hover(bool state);
			StyleSetElement* press(bool state);
		};
	}
}

