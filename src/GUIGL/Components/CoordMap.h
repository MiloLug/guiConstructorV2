#pragma once
#include <map>
#include <unordered_set>
#include <mutex>

namespace GUI {
	namespace Elements {
		class Element;
	}
	struct CoordPath;

	class CoordMap
	{
	public:
		std::recursive_mutex m;
		typedef std::unordered_set<Elements::Element*> list_elementsSet_t;
		typedef std::map<const int, void*> list_coordMap_t;

		list_coordMap_t coordList;

		//virtual void reviewCoordList();
		virtual CoordPath add(int z, int x, int y, int w, int h, Elements::Element* elem);
		virtual void remove(CoordPath* path);
		virtual void move(CoordPath* path, int tz, int tx, int ty, int tw, int th);
		virtual Elements::Element* find(int x, int y);
	};

	struct CoordPath {
		int zPos;
		CoordMap::list_coordMap_t* z;
		int xPos;
		CoordMap::list_coordMap_t* x;
		int yPos;
		CoordMap::list_coordMap_t* y;
		int wPos;
		CoordMap::list_coordMap_t* w;
		int hPos;
		CoordMap::list_elementsSet_t* h;
		Elements::Element* elem;
	};
}

