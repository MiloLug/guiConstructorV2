#include "ElementContainer.h"
#include "Window.h"

#include <iostream>
namespace GUI {
	namespace Elements {
		//base type info =========================
		const std::type_info* ElementContainer::__base_type = &typeid(ElementContainer);
		const std::type_info* ElementContainer::__current_type() {
			return &typeid(ElementContainer);
		}
		//attributes =========================

		//data =========================
		inline Window* ElementContainer::parentWindow() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			return this->_parentWindow;
		}

		inline Element* ElementContainer::parentWindow(Window* w) {
			std::scoped_lock l(this->Element::m, this->Container::m);
			this->Element::parentWindow(w);
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->parentWindow(w);
			}
			return this;
		}

		inline Element* ElementContainer::parentWindowForceMove(Window* w) {
			std::scoped_lock l(this->Element::m, this->Container::m);

			if (w != this->_parentWindow){
				this->parentWindow(w);
			}
			else if(w != nullptr){
				this->__updatePos();
			}

			return this;
		}

		inline Element* ElementContainer::parent() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			return this->_parent;
		}

		inline Element* ElementContainer::parent(Element* el) {
			std::scoped_lock l(this->Element::m, this->Container::m);
			this->Element::parent(el);
			return this;
		}

		//constructor =========================
		ElementContainer::ElementContainer() : Element(), Container() {}

		//some methods =========================
		ElementContainer* ElementContainer::addElement(Element* elem) {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (elem->parent() != nullptr) {
				if (elem->parent() == this)
					return this;
				((ElementContainer*)elem->parent())->unlinkElement(elem);
			}
			elem->parent(this)
				->__linkContainer(this);
			this->elements.insert(elem);
			return this;
		};
		ElementContainer* ElementContainer::removeElement(Element* elem) {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (elem->parent() == this) {
				elem->removeSelf();
			}
			return this;
		};

		inline ElementContainer* ElementContainer::linkElement(Element* elem) {
			return this->addElement(elem);
		};

		ElementContainer* ElementContainer::unlinkElement(Element* elem) {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (elem->parent() == this) {
				elem->parent(nullptr)
					->__unlinkContainer(this);
				this->elements.erase(elem);
			}
			return this;
		};

		ElementContainer* ElementContainer::unlinkAll() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->parent(nullptr)
					->__unlinkContainer(this);
			}
			this->elements.clear();
			return this;
		};
		ElementContainer* ElementContainer::removeAll() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			std::unordered_set<Element*>::iterator iter = this->elements.begin();
			Element* tmp;
			while (iter != this->elements.end()) {
				tmp = *iter;
				iter = this->elements.erase(iter);
				tmp->parent(nullptr);
				if (tmp->__containersCount() == 0)
					tmp->removeSelf();
				else
					tmp->__unlinkContainer(this);
			}
			return this;
		};

		void ElementContainer::__drawBase(int wwidth, int wheight) {}


		inline Element* ElementContainer::__updateLeft() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (this->parentWindow() == nullptr)
				return this;
			this->Element::__updateLeft();
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->__updateLeft();
			}
			return this;
		}

		inline Element* ElementContainer::__updateTop() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (this->parentWindow() == nullptr)
				return this;
			this->Element::__updateTop();
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->__updateTop();
			}
			return this;
		}

		inline Element* ElementContainer::__updateZ() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (this->parentWindow() == nullptr)
				return this;
			this->Element::__updateZ();
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->__updateZ();
			}
			return this;
		}

		inline Element* ElementContainer::__updatePos() {
			std::scoped_lock l(this->Element::m, this->Container::m);
			if (this->parentWindow() == nullptr)
				return this;
			this->Element::__updatePos();
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->__updatePos();
			}
			return this;
		};


		void ElementContainer::removeSelf() {
			this->removeAll()
				->Element::removeSelf();
		}
		ElementContainer::~ElementContainer() {}
	}
}