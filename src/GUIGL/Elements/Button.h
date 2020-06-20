#pragma once
#include <functional>
#include "Element.h"

namespace GUI {
	namespace Elements {
		class Button : public Element{
		public:
			static const std::type_info* __base_type;
			const std::type_info* __current_type;

			Button(elemId_t id, elemId_t parentWindow = 0, elemId_t parent = 0);

			virtual void __drawBase(int wwidth, int wheight);

			virtual ~Button();
			virtual void removeSelf();
		};
	}
}

