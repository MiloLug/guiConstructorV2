#include "CoordMap.h"
#include "../Elements/Element.h"

namespace GUI {
	
	CoordPath CoordMap::add(int z, int x, int y, int w, int h, Elements::Element* elem) {
		std::lock_guard<std::recursive_mutex> g(this->m);
		std::pair<list_coordMap_t::iterator, bool> tmp = this->coordList.emplace(z, nullptr);
		CoordPath path;
		path.zPos = z;
		path.xPos = x;
		path.yPos = y;
		path.wPos = w;
		path.hPos = h;

		if (tmp.second) {
			tmp.first->second = new list_coordMap_t;
		}
		path.z = (list_coordMap_t*)tmp.first->second;

		tmp = path.z->emplace(x, nullptr);
		if (tmp.second) {
			tmp.first->second = new list_coordMap_t;
		}
		path.x = (list_coordMap_t*)tmp.first->second;

		tmp = path.x->emplace(y, nullptr);
		if (tmp.second) {
			tmp.first->second = new list_coordMap_t;
		}
		path.y = (list_coordMap_t*)tmp.first->second;

		tmp = path.y->emplace(w, nullptr);
		if (tmp.second) {
			tmp.first->second = new list_coordMap_t;
		}
		path.w = (list_coordMap_t*)tmp.first->second;

		tmp = path.w->emplace(h, nullptr);
		if (tmp.second) {
			tmp.first->second = new list_elementsSet_t;
		}
		path.h = (list_elementsSet_t*)tmp.first->second;

		path.h->insert(elem);
		path.elem = elem;
		return path;
	};


	void CoordMap::remove(CoordPath* path) {
		std::lock_guard<std::recursive_mutex> g(this->m);
		path->h->erase(path->elem);
		if (path->h->empty()) {
			delete path->h;
			path->w->erase(path->hPos);
			if (path->w->empty()) {
				delete path->w;
				path->y->erase(path->wPos);
				if (path->y->empty()) {
					delete path->y;
					path->x->erase(path->yPos);
					if (path->x->empty()) {
						delete path->x;
						path->z->erase(path->xPos);
						if (path->z->empty()) {
							delete path->z;
							this->coordList.erase(path->zPos);
						}
					}
				}
			}
		}
	};


	void CoordMap::move(CoordPath* path,int tz, int tx, int ty, int tw, int th) {
		std::lock_guard<std::recursive_mutex> g(this->m);
		if (path->zPos == tz && path->xPos == tx && path->yPos == ty && path->wPos == tw && path->hPos == th)
			return;

		CoordPath tmp = this->add(tz, tx, ty, tw, th, path->elem);
		this->remove(path);
		path->zPos = tz;
		path->xPos = tx;
		path->yPos = ty;
		path->wPos = tw;
		path->hPos = th;

		path->z = tmp.z;
		path->x = tmp.x;
		path->y = tmp.y;
		path->w = tmp.w;
		path->h = tmp.h;
	};



	Elements::Element* CoordMap::find(int x, int y) {
		std::lock_guard<std::recursive_mutex> g(this->m);
		list_coordMap_t* xList,
			* yList,
			* wList,
			* hList;
		list_coordMap_t::reverse_iterator itZ, itX, itY, itW, itH,
			endZ, endX, endY, endW, endH;
		list_elementsSet_t* eList;

		int tmpw, tmph;


		endZ = this->coordList.rend();
		for (itZ = this->coordList.rbegin(); itZ != endZ; ++itZ) {
			xList = (list_coordMap_t*)itZ->second;
			endX = xList->rend();
			for (itX = xList->rbegin(); itX != endX; ++itX) {
				if (itX->first > x)
					continue;
				tmpw = x - itX->first;
				yList = (list_coordMap_t*)itX->second;
				endY = yList->rend();
				for (itY = yList->rbegin(); itY != endY; ++itY) {
					if (itY->first > y)
						continue;
					tmph = y - itY->first;
					wList = (list_coordMap_t*)itY->second;
					endW = wList->rend();
					for (itW = wList->rbegin(); itW != endW && !(itW->first < tmpw); ++itW) {
						hList = (list_coordMap_t*)itW->second;
						endH = hList->rend();
						for (itH = hList->rbegin(); itH != endH && !(itH->first < tmph); ++itH) {
							eList = (list_elementsSet_t*)itH->second;
							if (!eList->empty()) {
								return *eList->begin();
							}
						}
					}
				}
			}
		}
		return nullptr;
	};
}

