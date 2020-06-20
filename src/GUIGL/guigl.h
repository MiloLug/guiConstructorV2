#pragma once
#ifndef __GUIGL

#define __GUIGL

#include "common.h"
#include "glall.h"
#include "Elements/Elements.h"
#include "Event.h"
#include "Draw.h"
#include "GL/VAO.h"
#include "GLFW/SysWindow.h"

namespace GUI {
	extern bool glfwInitialized;

	void init();
	void runLoop();
	void terminate();
}

#endif