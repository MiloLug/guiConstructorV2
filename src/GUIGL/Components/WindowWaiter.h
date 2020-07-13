#pragma once
#include <unordered_set>
#include <mutex>

namespace GUI {
	namespace Elements {
		class Window;
	}
	class Container;
	class WindowWaiter {
	private:
	public:
		static Container* windows;
		static std::mutex m;
		static void addWindow(Elements::Window* w);
		static bool empty();
		static void saveContext();

		static void init();
		static void terminate();
	};
}