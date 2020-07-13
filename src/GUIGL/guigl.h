#pragma once


namespace GUI {
	//extern bool glfwInitialized;
	void init(size_t eventThreadsNumber);
	void terminate(bool dontWaitEventFunctions = false);
}
