#pragma once
#include "../common.h"
#include <string>
#include <functional>
#include <map>
#include <unordered_set>
#include "../GLFW/SysWindow.h"
#include "ElementContainer.h"

struct GLFWwindow;
namespace GUI {
	class CoordMap;
	namespace Elements {
		class Element;
		class Window : public ElementContainer, public SysWindow {
		public:
			//base type info =========================
			static const std::type_info* __base_type;
			virtual const std::type_info* __current_type();
			//attributes =========================

			//data =========================
			bool nativeResizing = false;

			CoordMap* coordMap;

			inline virtual Window* parentWindow();
			inline virtual Element* parent();
			inline virtual Element* parentWindow(Window* w);
			inline virtual Element* parent(Element* el);
			//constructor =========================
			Window(int width, int height, const std::string& title = "...");
			Window(const Window& win) = delete;
			Window(const Window* win) = delete;

			//some methods =========================
			virtual void __drawBase(int wwidth, int wheight);

			static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void cursorPosCallbackFn(GLFWwindow* window, double xpos, double ypos);
			static void cursorEnterCallback(GLFWwindow* window, int entered);
			static void closeCallbackFn(GLFWwindow* window);
			static void mouseButtonCallbackFn(GLFWwindow* window, int button, int action, int mods);


			inline virtual Window* __updateHeight();

			inline virtual Window* __updateWidth();

			inline virtual Window* __updateLeft();

			inline virtual Window* __updateTop();

			inline virtual Window* __updateZ();

			inline virtual Window* __updatePos();


			virtual void removeSelf();
			virtual ~Window();
		};
	}
}