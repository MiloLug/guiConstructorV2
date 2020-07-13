#pragma once
#include <stdexcept>
#include <string>

struct GLFWwindow;
namespace GUI {
	class SysWindow
	{
	public:
		GLFWwindow* instance;
		SysWindow(int width, int height, std::string title);
		SysWindow(const SysWindow& copy) = delete;
		void makeContextCurrent();
		void swapBuffers();
		void setUserPointer(void* point);

		void framebufferSizeCallback(void(*fn)(GLFWwindow*, int, int));
		void cursorPosCallback(void(*fn)(GLFWwindow*, double, double));
		void cursorEnterCallback(void(*fn)(GLFWwindow*, int));
		void closeCallback(void(*fn)(GLFWwindow*));
		void mouseButtonCallback(void(*fn)(GLFWwindow*, int, int, int));

		bool shouldClose();
		~SysWindow();
	};
}