#pragma once
#include <unordered_set>
#include <map>
#include "../../common.h"
#include <mutex>
#include "../EventCollection/classNameChange.h"


namespace GUI {
	namespace Elements {
		class Element;
	}
	namespace ClassName {
		class NameContainer{
			//typedef std::map<elemIdNum_t, std::unordered_set<Elements::Element*>> elements;
		public:
			std::vector<HashId> names;
			Elements::Element* el = nullptr;

			std::mutex m;

			void addName(const HashId& name);

			NameContainer(Elements::Element* el);
			inline void push(const std::string& name) {
				this->addName(name);
			}
			inline void push(const char* name) {
				this->addName(name);
			}
		};
	}
}