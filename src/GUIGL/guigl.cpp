#include "guigl.h"
#include <stdexcept>

namespace GUI {
	bool glfwInitialized = false;

	void init() {
		Event::init();
		if (!glfwInit()) {
			throw std::runtime_error("GUIGL: GLFW initialization failed");
		};
		glfwInitialized = true;
	}

	void runLoop() {
		while (1) {
			Draw::draw();
			Elements::ElementsStore::removeClosed();
			glfwPollEvents();
			Event::execAll();
			if (!Elements::ElementsStore::list.size())
				return;
		}
	}

	void terminate() {
		glfwTerminate();
		Draw::terminate();
		Elements::ElementsStore::terminate();
		//Event::terminate();
		//Event::terminateEvent();
	}
}