#include "SysWindow.h"

namespace GUI {
	SysWindow::SysWindow(int width, int height, std::string title) {
		if (!glfwInit()) {
			throw std::runtime_error("GUIGL: GLFW initialization failed");
		}
		this->instance = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}

	void SysWindow::makeContextCurrent() {
		glfwMakeContextCurrent(this->instance);
	}

	void SysWindow::swapBuffers() {
		glfwSwapBuffers(this->instance);
	}
	bool SysWindow::shouldClose() {
		return glfwWindowShouldClose(this->instance);
	}
	void SysWindow::setUserPointer(void* point) {
		glfwSetWindowUserPointer(this->instance, point);
	};

	void SysWindow::framebufferSizeCallback(void(*fn)(GLFWwindow*, int, int)) {
		glfwSetFramebufferSizeCallback(this->instance, fn);
	};
	void SysWindow::cursorPosCallback(void(*fn)(GLFWwindow*, double, double)) {
		glfwSetCursorPosCallback(this->instance, fn);
	};
	void SysWindow::cursorEnterCallback(void(*fn)(GLFWwindow*, int)) {
		glfwSetCursorEnterCallback(this->instance, fn);
	};
	void SysWindow::closeCallback(void(*fn)(GLFWwindow*)) {
		glfwSetWindowCloseCallback(this->instance, fn);
	};
	void SysWindow::mouseButtonCallback(void(*fn)(GLFWwindow*, int, int, int)) {
		glfwSetMouseButtonCallback(this->instance, fn);
	};

	SysWindow::~SysWindow() {
		glfwDestroyWindow(this->instance);
	}
}