#pragma once
#ifndef __GLFW_SYSWINDOW

#define __GLFW_SYSWINDOW

#include <stdexcept>
#include <GLFW/glfw3.h>
#include <string>

namespace GUI {
	class SysWindow
	{
	public:
		GLFWwindow* instance;
		SysWindow(int width, int height, std::string title);
		SysWindow(const SysWindow& copy) = delete;
		//setFullscreen(GLFWmonitor *monitor);
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

#endif