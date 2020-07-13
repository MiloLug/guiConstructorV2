#include "WindowWaiter.h"
#include "Container.h"
#include "../Elements/Window.h"

namespace GUI {
	std::mutex WindowWaiter::m;
	Container* WindowWaiter::windows;

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

	void WindowWaiter::init() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		WindowWaiter::windows = new Container;
	}
	void WindowWaiter::terminate() {
		std::lock_guard<std::mutex> guard(WindowWaiter::m);
		WindowWaiter::windows = new Container;
	}
}