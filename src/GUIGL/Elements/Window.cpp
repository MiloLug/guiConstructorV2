#include "Window.h"
#include "Element.h"
#include <GLFW/glfw3.h>
#include "../Components/EventCollection/mouseMove.h"
#include "../Components/EventCollection/mouseDown.h"
#include "../Components/EventCollection/mouseUp.h"
#include "../Components/WindowWaiter.h"
#include "../Components/CoordMap.h"

namespace GUI {
	namespace Elements {
		//base type info =========================
		const std::type_info* Window::__base_type = &typeid(Window);
		const std::type_info* Window::__current_type() {
			return &typeid(Window);
		}
		//attributes =========================

		//data =========================
		inline Window* Window::parentWindow() {
			return this;
		}
		inline Element* Window::parent() {
			return nullptr;
		}
		inline Element* Window::parentWindow(Window* w) {
			return this;
		}
		inline Element* Window::parent(Element* el) {
			return this;
		}
		//constructor =========================
		Window::Window(int width, int height, const std::string& title) : ElementContainer(), SysWindow(width, height, title) {
			this->coordMap = new CoordMap;
			WindowWaiter::addWindow(this);
			this->setUserPointer(this);
			//this->framebufferSizeCallback(Window::framebufferSizeCallback);
			this->cursorPosCallback(Window::cursorPosCallbackFn);
			//this->cursorEnterCallback(Window::cursorEnterCallback);
			this->closeCallback(Window::closeCallbackFn);
			this->mouseButtonCallback(Window::mouseButtonCallbackFn);
		}

		//some methods =========================
		void Window::__drawBase(int wwidth, int wheight) {
			/*if (!this->nativeResizing) {
				glfwSetWindowSize(this->sysWindow->instance, this->style->_width, this->style->_height);
			}
			else
				this->nativeResizing = false;
			glfwSetWindowTitle(this->sysWindow->instance, this->_title.data());
			glClearColor(this->style->_background[0], this->style->_background[1], this->style->_background[2], this->style->_background[3]);
			glClear(GL_COLOR_BUFFER_BIT);*/
		}


		

		/*Window* Window::removeFromCoordList(int z, int x, int y, int w, int h, Element* elem) {
			Window::list_coordMap_t* xList,
				* yList,
				* wList,
				* hList;
			Window::list_elementsSet_t* eList;
			Window::list_coordMap_t::iterator coordIter1, coordIter2, coordIter3, coordIter4, coordIter5;

			std::lock_guard<std::recursive_mutex> g(this->Element::m);

			coordIter1 = this->coordList.find(z);
			if (coordIter1 != this->coordList.end()) {
				xList = (Window::list_coordMap_t*)coordIter1->second;

				coordIter2 = xList->find(x);
				if (coordIter2 != xList->end()) {
					yList = (Window::list_coordMap_t*)coordIter2->second;

					coordIter3 = yList->find(y);
					if (coordIter3 != yList->end()) {
						wList = (Window::list_coordMap_t*)coordIter3->second;

						coordIter4 = wList->find(w);
						if (coordIter4 != wList->end()) {
							hList = (Window::list_coordMap_t*)coordIter4->second;

							coordIter5 = hList->find(h);
							if (coordIter5 != hList->end()) {
								eList = (Window::list_elementsSet_t*)coordIter5->second;
								eList->erase(elem);
								if (eList->empty()) {
									delete eList;
									hList->erase(coordIter5);
								}
							}
							if (hList->empty()) {
								delete hList;
								wList->erase(coordIter4);
							}
						}
						if (wList->empty()) {
							delete wList;
							yList->erase(coordIter3);
						}
					}
					if (yList->empty()) {
						delete yList;
						xList->erase(coordIter2);
					}
				}
				if (xList->empty()) {
					delete xList;
					this->coordList.erase(coordIter1);
				}
			}

			return this;
		};*/
		

		/*Window* Window::moveInCoordList(int fz, int fx, int fy, int fw, int fh,
			int tz, int tx, int ty, int tw, int th, Element* elem) {

			if (fz == tz && fx == tx && fy == ty && fw == tw && fh == th)
				return this;

			Window::list_coordMap_t* xList,
				* yList,
				* wList,
				* hList;
			Window::list_elementsSet_t* eList;
			Window::list_coordMap_t::iterator coordIter1, coordIter2, coordIter3, coordIter4, coordIter5;

			std::lock_guard<std::recursive_mutex> g(this->Element::m);

			coordIter1 = this->coordList.find(fz);
			if (coordIter1 != this->coordList.end()) {
				xList = (Window::list_coordMap_t*)coordIter1->second;

				coordIter2 = xList->find(fx);
				if (coordIter2 != xList->end()) {
					yList = (Window::list_coordMap_t*)coordIter2->second;

					coordIter3 = yList->find(fy);
					if (coordIter3 != yList->end()) {
						wList = (Window::list_coordMap_t*)coordIter3->second;

						coordIter4 = wList->find(fw);
						if (coordIter4 != wList->end()) {
							hList = (Window::list_coordMap_t*)coordIter4->second;

							coordIter5 = hList->find(fh);
							if (coordIter5 != hList->end()) {
								eList = (Window::list_elementsSet_t*)coordIter5->second;
								eList->erase(elem);
								if (eList->empty()) {
									delete eList;
									hList->erase(coordIter5);
								}
							}
							if (fw != tw && hList->empty()) {
								delete hList;
								wList->erase(coordIter4);
							}
						}
						if (fy != ty && wList->empty()) {
							delete wList;
							yList->erase(coordIter3);
						}
					}
					if (fx != tx && yList->empty()) {
						delete yList;
						xList->erase(coordIter2);
					}
				}
				if (fz != tz && xList->empty()) {
					delete xList;
					this->coordList.erase(coordIter1);
				}
			}

			this->addToCoordList(tz, tx, ty, tw, th, elem);

			return this;
		};*/

		

		void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp = new Event::framebufferSizeEvent(width, height);
			tmp->window = _this->id;
			Event::emit(__EVENT_FRAMEBUFFER_SIZE, tmp);
			Event::execAll();

			_this->nativeResizing = true;
			_this->style->_width = width;
			_this->style->_height = height;
			_this->__redraw = true;

			Draw::draw();*/
		}
		void Window::cursorPosCallbackFn(GLFWwindow* window, double xpos, double ypos) {
			Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Element* top = _this->coordMap->find(xpos, ypos);
			(top == nullptr ? _this : top)->emit(
				Event::EventCollection::mouseMove::eventId,
				new Event::EventCollection::mouseMove(xpos, ypos)
			);
		}
		void Window::closeCallbackFn(GLFWwindow* window) {
			Window* _this = (Window*)glfwGetWindowUserPointer(window);
			_this->removeSelf();
			/*Event::baseEvent* tmp = new Event::closeEvent();
			tmp->window = _this->id;
			Event::emit(__EVENT_CLOSE, tmp);*/
		}
		void Window::cursorEnterCallback(GLFWwindow* window, int entered) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp;
			if (entered) {
				tmp = new Event::windowMouseEnterEvent();
				tmp->window = _this->id;
				Event::emit(__EVENT_WINDOW_MOUSE_ENTER, tmp);
			}
			else {
				tmp = new Event::windowMouseLeaveEvent();
				tmp->window = _this->id;
				Event::emit(__EVENT_WINDOW_MOUSE_LEAVE, tmp);
			}*/
		};
		void Window::mouseButtonCallbackFn(GLFWwindow* window, int button, int action, int mods) {
			Window* _this = (Window*)glfwGetWindowUserPointer(window);
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			Element* top = _this->coordMap->find(xpos, ypos);

			if (action == GLFW_PRESS)
				(top == nullptr ? _this : top)->emit(
					Event::EventCollection::mouseDown::eventId,
					new Event::EventCollection::mouseDown(xpos, ypos, (Event::EventCollection::MouseButtons)button)
				);
			else
				(top == nullptr ? _this : top)->emit(
					Event::EventCollection::mouseUp::eventId,
					new Event::EventCollection::mouseUp(xpos, ypos, (Event::EventCollection::MouseButtons)button)
				);
		}


		inline Window* Window::__updateHeight(){
			glfwSetWindowSize(this->instance, this->style->width(), this->style->height());
			std::lock_guard<std::recursive_mutex> g(this->Element::m);
			return this;
		};

		inline Window* Window::__updateWidth() {
			glfwSetWindowSize(this->instance, this->style->width(), this->style->height());
			std::lock_guard<std::recursive_mutex> g(this->Element::m);
			return this;
		};

		inline Window* Window::__updateLeft() {
			std::lock_guard<std::recursive_mutex> g(this->Element::m);
			return this;
		};

		inline Window* Window::__updateTop() {
			std::lock_guard<std::recursive_mutex> g(this->Element::m);
			return this;
		};

		inline Window* Window::__updateZ() {
			return this;
		};

		inline Window* Window::__updatePos() {
			glfwSetWindowSize(this->instance, this->style->width(), this->style->height());
			std::lock_guard<std::recursive_mutex> g(this->Element::m);

			return this;
		};


		void Window::removeSelf() {
			this->ElementContainer::removeSelf();
		}
		Window::~Window() {
			delete this->coordMap;
			WindowWaiter::saveContext();
			//delete this->sysWindow;
		}
	}
}