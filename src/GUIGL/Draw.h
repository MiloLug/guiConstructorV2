#pragma once
#ifndef __GUIGL_DRAW

#define __GUIGL_DRAW

#include "common.h"
#include <vector>
#include <map>
#include <stack>
#include "Elements/Element.h"

namespace GUI {
	class Draw
	{
	public:
		typedef std::pair<int, std::vector<Elements::Element*>*> zIndexesPair_t;
		typedef std::map<int, std::vector<Elements::Element*>*> zIndexesMap_t;
		typedef std::map<elemId_t, zIndexesMap_t*> windowsMap_t;
		typedef std::pair<elemId_t, zIndexesMap_t*> windowsPair_t;
		
		static windowsMap_t list;
		static bool allowDraw;
		static std::stack<elemId_t> toDraw;

		static bool canWindowDraw(elemId_t wid);
		
		static void removeWindowMap(elemId_t wid);
		static void terminate();

		static void review();
		static void draw();
	};
}

#endif

