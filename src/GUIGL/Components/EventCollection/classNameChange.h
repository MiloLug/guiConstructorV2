#pragma once

#include "eventElement.h"
#include <vector>
#include "../../common.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class classNameChange : public eventElement {
			public:
				static elemIdNum_t eventId;

				std::vector<HashId> newNames;
				classNameChange(Elements::Element* topElement, const std::vector<HashId>& n) : eventElement(topElement){
					this->newNames = n;
				}
				classNameChange() {}
				virtual classNameChange* copy() {
					classNameChange* t = new classNameChange(this->topElement, this->newNames);
					return t;
				}
				virtual ~classNameChange() {}
			};
		}
	}
}