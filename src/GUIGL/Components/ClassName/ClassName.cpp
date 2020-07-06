#include "ClassName.h"
#include "../../Elements/Element.h"
#include "../Event/Emitter.h"

namespace GUI {
	namespace ClassName {

		void NameContainer::addName(const HashId& name) {
			this->m.lock();
			std::vector<HashId>::iterator beg = this->names.begin(),
				end = this->names.end();
			for (; beg != end; beg++) {
				if (*beg == name) {
					return;
				}
			}
			names.push_back(name);
			this->el->emit(
				Event::EventCollection::classNameChange::eventId,
				new Event::EventCollection::classNameChange(this->names)
			);
			this->m.unlock();
			//ClassNamesStorage::addPair(name, this->el);
		}

		NameContainer::NameContainer(Elements::Element* el) {
			this->el = el;
		}
	}
}