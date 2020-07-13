#include "guigl.h"
#include <iostream>
#include <stdexcept>
#include "Components/WindowWaiter.h"
#include "Components/Event/Emitter.h"
#include "Components/Style/StyleStorage.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
namespace GUI {
	//bool glfwInitialized = false;

	void init(size_t eventThreadsNumber) {
		Event::init(eventThreadsNumber);
		WindowWaiter::init();
		if (!glfwInit()) {
			throw std::runtime_error("GUIGL: GLFW initialization failed");
		};
	}

	//void runLoop() {
	//	while (1) {
	//		Draw::draw();
	//		Elements::ElementsStore::removeClosed();
	//		glfwPollEvents();
	//		Event::execAll();
	//		if (!Elements::ElementsStore::list.size())
	//			return;
	//	}
	//}

	void terminate(bool dontWaitEventFunctions) {
		while (!WindowWaiter::empty()) {
			//DRAW
			//std::cout << "1" ;
			
			glfwPollEvents();
		}
		WindowWaiter::terminate();
		Event::terminate(dontWaitEventFunctions);
		Event::wait();
		Style::StylesStorage::terminate();
		glfwTerminate();
	}
}