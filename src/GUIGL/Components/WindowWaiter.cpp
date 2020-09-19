#include "WindowWaiter.h"
#include "Container.h"
#include "../Elements/Window.h"
#include <functional>

namespace GUI {
	std::mutex WindowWaiter::m;
	Container* WindowWaiter::windows = nullptr;

	void WindowWaiter::addWindow(Elements::Window* w) {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		WindowWaiter::windows->linkElement(w);
	}

	bool WindowWaiter::empty() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		return WindowWaiter::windows->elements.empty();
	}

	void WindowWaiter::saveContext() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		auto beg = WindowWaiter::windows->elements.begin();
		if (beg != WindowWaiter::windows->elements.end()) {
			((Elements::Window*)(*beg))->makeContextCurrent();
		}
	}

	void WindowWaiter::iterateContexts(std::function<void(Elements::Window*)> fn) {
		for (Elements::Element* window : WindowWaiter::windows->elements) {
			((Elements::Window*)window)->makeContextCurrent();
			fn((Elements::Window*)window);
		}
	};

	void WindowWaiter::init() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		WindowWaiter::windows = new Container;
	}
	void WindowWaiter::terminate() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		if(WindowWaiter::windows != nullptr)
			WindowWaiter::windows->removeSelf();
	}
}