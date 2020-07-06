#pragma once

#include "../Event/DataPack.h"
#include <vector>
#include "../../common.h"

namespace GUI {
	namespace Event {
		namespace EventCollection {
			class classNameChange : public DataPack {
			public:
				static elemIdNum_t eventId;

				std::vector<HashId> newNames;
				classNameChange(const std::vector<HashId>& n) {
					this->newNames = n;
				}
				classNameChange() {}
				virtual classNameChange* copy() {
					classNameChange* t = new classNameChange(this->newNames);
					return t;
				}
				virtual ~classNameChange() {}
			};
		}
	}
}