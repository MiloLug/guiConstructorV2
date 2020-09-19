#include "Element.h"
#include "../common.h"
#include "Window.h"
#include "../Components/Container.h"

namespace GUI {
	namespace Elements {
		//base type info =========================
		const std::type_info* Element::__base_type = &typeid(Element);
		const std::type_info* Element::__current_type() {
			return &typeid(Element);
		}
		//attributes =========================
		std::string Element::title() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_title;
		};
		Element* Element::title(const std::string& title) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->_title = title;
			//this->windowRedraw(); //?
			return this;
		};

		//data =========================
		inline Window* Element::parentWindow() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_parentWindow;
		}
		inline Element* Element::parent() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			return this->_parent;
		}
		inline Element* Element::parentWindow(Window* w) {
			std::lock_guard<std::recursive_mutex> g(this->m);

			if (w != this->_parentWindow) {
				if (this->_parentWindow != nullptr)
					this->_parentWindow->coordMap->remove(&this->_coordPath);

				this->_parentWindow = w;
				if (w != nullptr) {
					this->_coordPath = w->coordMap->add(this->style->zIndex(), this->style->left(), this->style->top(), this->style->width(), this->style->height(), this);
				}
			}
			return this;
		}
		inline Element* Element::parentWindowForceMove(Window* w) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (w != this->_parentWindow || w == nullptr) {
				if (this->_parentWindow != nullptr)
					this->_parentWindow->coordMap->remove(&this->_coordPath);

				this->_parentWindow = w;
				if (w != nullptr) {
					this->_coordPath = w->coordMap->add(this->style->zIndex(), this->style->left(), this->style->top(), this->style->width(), this->style->height(), this);
				}
			}
			else {
				this->__updatePos();
			}
			return this;
		}
		inline Element* Element::parent(Element* el) {
			std::lock_guard<std::recursive_mutex> g(this->m);

			if (el != this->_parent && el != this) {
				this->_parent = el;
				Window* w = el != nullptr ? el->parentWindow() : nullptr;
				this->parentWindowForceMove(w);
			}
			return this;
		}
		//constructor =========================
		Element::Element() {
			this->style = new Style::StyleSetElement(this);
			this->className = new ClassName::NameContainer(this);
		}

		//some methods =========================
		void Element::__drawBase(int wwidth, int wheight) {}

		//?
		/*Element* Element::windowReviewZ() {
			Window* w = (Window*)ElementsStore::getElement(this->parentWindow, this->parentWindow);
			if (w != nullptr)
				w->__reviewZ = true;
			return this;
		}
		Element* Element::windowRedraw() {
			Window* w = (Window*)ElementsStore::getElement(this->parentWindow, this->parentWindow);
			if (w != nullptr)
				w->__redraw = true;
			return this;
		}*/

		Element* Element::hide() {
			return this;
		}
		Element* Element::show() {
			return this;
		}


		inline Element* Element::__linkContainer(Container* cont) {
			this->containers.insert(cont);
			return this;
		};
		inline Element* Element::__unlinkContainer(Container* cont) {
			this->containers.erase(cont);
			return this;
		};
		inline size_t Element::__containersCount() {
			return this->containers.size();
		};
		

		inline Element* Element::__updateHeight() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->parentWindow() == nullptr)
				return this;
			this->parentWindow()->coordMap->move(
				&this->_coordPath,
				this->_coordPath.zPos, this->_coordPath.xPos, this->_coordPath.yPos, this->_coordPath.wPos, this->style->height()
			);
			return this;
		}

		inline Element* Element::__updateWidth() {
		std::lock_guard<std::recursive_mutex> g(this->m);
		if (this->parentWindow() == nullptr)
			return this;
		this->parentWindow()->coordMap->move(
			&this->_coordPath,
			this->_coordPath.zPos, this->_coordPath.xPos, this->_coordPath.yPos, this->style->width(), this->_coordPath.hPos
		);
		return this;
		}

		inline Element* Element::__updateLeft() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->parentWindow() == nullptr)
				return this;
			this->parentWindow()->coordMap->move(
				&this->_coordPath,
				this->_coordPath.zPos, this->style->left(), this->_coordPath.yPos, this->_coordPath.wPos, this->_coordPath.hPos
			);
			return this;
		}

		inline Element* Element::__updateTop() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->parentWindow() == nullptr)
				return this;
			this->parentWindow()->coordMap->move(
				&this->_coordPath,
				this->_coordPath.zPos, this->_coordPath.xPos, this->style->top(), this->_coordPath.wPos, this->_coordPath.hPos
			);
			return this;
		}

		inline Element* Element::__updateZ() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->parentWindow() == nullptr)
				return this;
			this->parentWindow()->coordMap->move(
				&this->_coordPath,
				this->style->zIndex(), this->_coordPath.xPos, this->_coordPath.yPos, this->_coordPath.wPos, this->_coordPath.hPos
			);
			return this;
		}

		inline Element* Element::__updatePos() {
			std::lock_guard<std::recursive_mutex> g(this->m);
			if (this->parentWindow() == nullptr)
				return this;
			this->parentWindow()->coordMap->move(
				&this->_coordPath,
				this->style->zIndex(), this->style->left(), this->style->top(), this->style->width(), this->style->height()
			);
			return this;
		};

		inline Element* Element::emit(HashId id, Event::DataPack* data, bool propagation) {
			std::lock_guard<std::recursive_mutex> g(this->m);
			this->Emitter::emit(id, data->copy());
			if (propagation && this->parent() != nullptr) {
				this->parent()->emit(id, data->copy());
			}
			delete data;
			return this;
		};

		void Element::removeSelf() {
			this->m.lock();
			std::unordered_set<Container*>::iterator iter = this->containers.begin();
			Container* tmp;
			while (iter != this->containers.end()) {
				tmp = *iter;
				iter = this->containers.erase(iter);
				tmp->unlinkElement(this);
			}
			delete this->style;
			delete this->className;
			this->m.unlock();
			delete this;
		}
		Element::~Element() {

		}
	}
}