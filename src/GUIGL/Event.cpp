#include "Event.h"
#include "Elements/Element.h"
#include "Elements/ElementsStore.h"
#include "common.h"
#include <string>

#include <iostream>

namespace GUI {
	/* main event types
	=======================================================*/
	Event::baseEvent::~baseEvent() {}
	Event::baseEvent::baseEvent(bool isProtected) {
		this->isProtected = isProtected;
	}
	Event::baseEvent::baseEvent(const Event::baseEvent& base) {
		this->element = base.element;
		this->topElelemt = base.topElelemt;
		this->window = base.window;
		this->data = base.data;
	}

	Event::dataEvent::dataEvent(void* data) : baseEvent() {
		this->data = data;
	}
	Event::dataEvent::dataEvent(const Event::dataEvent& base) : baseEvent(base) {}
	Event::dataEvent::~dataEvent() {}

	Event::framebufferSizeEvent::framebufferSizeEvent(int width, int height) : baseEvent() {
		this->width = width;
		this->height = height;
	}
	Event::framebufferSizeEvent::framebufferSizeEvent(const Event::framebufferSizeEvent& base) : baseEvent() {
		this->Event::framebufferSizeEvent::framebufferSizeEvent(base.width, base.height);
		this->Event::baseEvent::baseEvent(base);
	}
	Event::framebufferSizeEvent::~framebufferSizeEvent() {}

	Event::mouseMoveEvent::mouseMoveEvent(double X, double Y) : baseEvent() {
		this->X = X;
		this->Y = Y;
	}
	Event::mouseMoveEvent::mouseMoveEvent(const Event::mouseMoveEvent& base){
		this->Event::mouseMoveEvent::mouseMoveEvent(base.X, base.Y);
		this->Event::baseEvent::baseEvent(base);
	}
	Event::mouseMoveEvent::~mouseMoveEvent() {}

	Event::mouseButtonEvent::mouseButtonEvent(double X, double Y, unsigned short int button) : baseEvent() {
		this->X = X;
		this->Y = Y;
		this->button = button;
	}
	Event::mouseButtonEvent::mouseButtonEvent(const Event::mouseButtonEvent& base){
		this->Event::mouseButtonEvent::mouseButtonEvent(base.X, base.Y, base.button);
		this->Event::baseEvent::baseEvent(base);
	}
	Event::mouseButtonEvent::~mouseButtonEvent() {}

	Event::closeEvent::closeEvent(const Event::closeEvent& base) : baseEvent(base) {}
	Event::closeEvent::~closeEvent() {}

	Event::windowMouseEnterEvent::windowMouseEnterEvent(const Event::windowMouseEnterEvent& base) : baseEvent(base) {}
	Event::windowMouseEnterEvent::~windowMouseEnterEvent() {}

	Event::windowMouseLeaveEvent::windowMouseLeaveEvent(const Event::windowMouseLeaveEvent& base) : baseEvent(base) {}
	Event::windowMouseLeaveEvent::~windowMouseLeaveEvent() {};

	/* process
	=======================================================*/
	Event::mainELElementsMap_t* Event::getListenerMembers(elemId_t wid, elemId_t eventId) {
		Event::mainELWindowsMap_t::const_iterator witer = Event::eventListenersStore.find(wid);
		if (witer != Event::eventListenersStore.end()) {
			Event::mainELTypes_t::const_iterator titer = witer->second->find(eventId);
			if (titer != witer->second->end()) {
				return titer->second;
			}
		}
		return nullptr;
	}

	void Event::emitFramebufferSize(Event::baseEvent* e) {
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(e->window, EVENT_FRAMEBUFFER_SIZE);
		e->eventId = EVENT_FRAMEBUFFER_SIZE;
		if (listeners != nullptr) {
			for (const Event::mainELElementsPair_t& tmp : *listeners) {
				for (char** arr : *tmp.second) {
					if (*(bool*)arr[2])
						continue;
					e->additionData = (void*)arr[1];
					(*(Event::defaultELFn*)arr[0])(e);
				}
			}
		}
	};

	void Event::emitMouseMove(Event::baseEvent* e) {
		int maxZ = 0;
		Elements::Element* topElement = nullptr;
		Elements::Element* etmp = nullptr;
		Event::mainELElementsMap_t::const_iterator eiter;
		Event::mouseMoveEvent* tmpev = (Event::mouseMoveEvent*)e;
		
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(e->window, e->eventId);
		if (listeners != nullptr) {
			for (const Event::mainELElementsPair_t& tmp : *listeners) {
				etmp = Elements::ElementsStore::getElement(e->window, tmp.first);
				if (etmp != nullptr) {
					if (maxZ <= etmp->style->zIndex()
						&& etmp->style->left() < tmpev->X
						&& etmp->style->left() + etmp->style->width() > tmpev->X
						&& etmp->style->top() < tmpev->Y
						&& etmp->style->top() + etmp->style->height() > tmpev->Y)
						maxZ = etmp->style->zIndex(),
						topElement = etmp;
				}
			}
		}
		if (topElement != nullptr) {
			etmp = topElement;
			e->topElelemt = topElement->id;
			while (etmp != nullptr) {
				eiter = listeners->find(etmp->id);
				if (eiter != listeners->end()) {
					e->element = etmp->id;
					for (char** arr : *eiter->second) {
						if (*(bool*)arr[2])
							continue;
						e->additionData = (void*)arr[1];
						(*(Event::defaultELFn*)arr[0])(e);
					}
				}
				etmp = Elements::ElementsStore::getElement(e->window, etmp->parent);
			}
		}
	};

	void Event::emitClose(Event::baseEvent* e) {
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(e->window, EVENT_CLOSE);
		e->eventId = EVENT_CLOSE;
		if (listeners != nullptr) {
			for (const Event::mainELElementsPair_t& tmp : *listeners) {
				for (char** arr : *tmp.second) {
					if (*(bool*)arr[2])
						continue;
					e->additionData = (void*)arr[1];
					(*(Event::defaultELFn*)arr[0])(e);
				}
			}
		}
	};

	void Event::emitWindowMouseEnter(Event::baseEvent* e) {
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(e->window, EVENT_WINDOW_MOUSE_ENTER);
		e->eventId = EVENT_WINDOW_MOUSE_ENTER;
		if (listeners != nullptr) {
			for (const Event::mainELElementsPair_t& tmp : *listeners) {
				for (char** arr : *tmp.second) {
					if (*(bool*)arr[2])
						continue;
					e->additionData = (void*)arr[1];
					(*(Event::defaultELFn*)arr[0])(e);
				}
			}
		}
	};

	void Event::emitWindowMouseLeave(Event::baseEvent* e) {
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(e->window, EVENT_WINDOW_MOUSE_LEAVE);
		e->eventId = EVENT_WINDOW_MOUSE_LEAVE;
		if (listeners != nullptr) {
			for (const Event::mainELElementsPair_t& tmp : *listeners) {
				for (char** arr : *tmp.second) {
					if (*(bool*)arr[2])
						continue;
					e->additionData = (void*)arr[1];
					(*(Event::defaultELFn*)arr[0])(e);
				}
			}
		}
	};

	std::vector<Event::mainEmitterPair_t*> Event::emittsStore;
	Event::mainELWindowsMap_t Event::eventListenersStore;
	Event::mainELWindowsMap_t Event::eventListenersRemoverStore;

	//window plain emitter
	void Event::emit(elemId_t wid, elemId_t eid, const elemId_t& eventId, Event::baseEvent* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = wid; tmp[1] = eid; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ e, tmp });
	}
	void Event::emit(elemId_t wid, elemId_t eid, const elemId_t& eventId, void* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = wid; tmp[1] = eid; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ new Event::dataEvent(e), tmp });
	}

	void Event::emit(elemId_t wid, const elemId_t& eventId, Event::baseEvent* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = wid; tmp[1] = 0; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ e, tmp });
	}
	void Event::emit(elemId_t wid, const elemId_t& eventId, void* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = wid; tmp[1] = 0; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ new Event::dataEvent(e), tmp });
	}
	void Event::on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const Event::defaultELFn& fn, void* additionalData, Event::defaultELFn*& listenerPtr) {
		if (wid != 0 && Elements::ElementsStore::getElement(wid, eid) == nullptr)
			return;

		listenerPtr = new Event::defaultELFn(fn);
		Event::mainELTypes_t* tmptypes;
		Event::mainELElementsMap_t* tmpelements;
		Event::mainELFnVector_t* tmpvec;
		if (Event::eventListenersStore.find(wid) == Event::eventListenersStore.end()) {
			tmptypes = new Event::mainELTypes_t;
			Event::eventListenersStore[wid] = tmptypes;
		}
		else
			tmptypes = Event::eventListenersStore[wid];

		if (tmptypes->find(eventId) == tmptypes->end()) {
			tmpelements = new Event::mainELElementsMap_t;
			tmptypes->operator[](eventId) = tmpelements;
		}
		else
			tmpelements = tmptypes->operator[](eventId);

		if (tmpelements->find(eid) == tmpelements->end()) {
			tmpvec = new Event::mainELFnVector_t;
			tmpelements->operator[](eid) = tmpvec;
		}
		else
			tmpvec = tmpelements->operator[](eid);

		char** arr = new char* [3];
		arr[0] = (char*)listenerPtr;
		arr[1] = (char*)additionalData;
		arr[2] = new char{ 0 };

		tmpvec->push_back(arr);
	}
	void Event::on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const Event::defaultELFn& fn, void* additionData) {
		Event::defaultELFn* listenerPtr;
		Event::on(wid, eid, eventId, fn, additionData, listenerPtr);
	};
	void Event::on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const Event::defaultELFn& fn, Event::defaultELFn*& listenerPtr) {
		Event::on(wid, eid, eventId, fn, nullptr, listenerPtr);
	};
	void Event::on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const Event::defaultELFn& fn) {
		Event::defaultELFn* listenerPtr;
		Event::on(wid, eid, eventId, fn, nullptr, listenerPtr);
	}

	void Event::addRemover(elemId_t wid, elemId_t eid, const elemId_t& eventId) {
		Event::mainELTypes_t* tmptypes;
		Event::mainELElementsMap_t* tmpelements;

		if (Event::eventListenersRemoverStore.find(wid) == Event::eventListenersRemoverStore.end()) {
			tmptypes = new Event::mainELTypes_t;
			Event::eventListenersRemoverStore[wid] = tmptypes;
		}
		else
			tmptypes = Event::eventListenersRemoverStore[wid];

		if (tmptypes->find(eventId) == tmptypes->end()) {
			tmpelements = new Event::mainELElementsMap_t;
			tmptypes->operator[](eventId) = tmpelements;
		}
		else
			tmpelements = tmptypes->operator[](eventId);

		if (tmpelements->find(eid) == tmpelements->end()) {
			tmpelements->operator[](eid) = nullptr;
		}
	};

	void Event::off(elemId_t wid, elemId_t eid, const elemId_t& eventId, const Event::defaultELFn& fn) {
		if (!fnCanBeCompared(fn))
			return;

		bool removerAdded = false;
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(wid, eventId);
		if (listeners != nullptr) {
			Event::mainELElementsMap_t::const_iterator eiter = listeners->find(eid);
			if (eiter != listeners->end()) {

				for (char** arr : *eiter->second) {
					if (*(bool*)arr[2])
						continue;
					if (fnEquals(fn, *(Event::defaultELFn*)arr[0])) {
						*(bool*)arr[2] = 1;
						if (!removerAdded) {
							Event::addRemover(wid, eid, eventId);
							removerAdded = true;
						}
					}
				}
			}
		}
	};
	void Event::off(elemId_t wid, elemId_t eid, const elemId_t& eventId, Event::defaultELFn* fn) {
		bool removerAdded = false;
		Event::mainELElementsMap_t* listeners = Event::getListenerMembers(wid, eventId);
		if (listeners != nullptr) {
			Event::mainELElementsMap_t::const_iterator eiter = listeners->find(eid);
			if (eiter != listeners->end()) {

				for (char** arr : *eiter->second) {
					if (*(bool*)arr[2])
						continue;
					if (fn == (Event::defaultELFn*)arr[0]) {
						*(bool*)arr[2] = 1;
						if (!removerAdded) {
							Event::addRemover(wid, eid, eventId);
							removerAdded = true;
						}
					}
				}
			}
		}
	};

	//root emitter
	void Event::emit(const elemId_t& eventId, Event::baseEvent* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = 0; tmp[1] = 0; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ e, tmp });
	}
	void Event::emit(const elemId_t& eventId, void* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = 0; tmp[1] = 0; tmp[2] = eventId;
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ new Event::dataEvent(e), tmp });
	}
	void Event::on(const elemId_t& eventId, const Event::defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr) {
		Event::on(0, 0, eventId, fn, additionData, listenerPtr);
	}
	void Event::on(const elemId_t& eventId, const Event::defaultELFn& fn, void* additionData) {
		Event::on(0, 0, eventId, fn, additionData);
	}
	void Event::on(const elemId_t& eventId, const Event::defaultELFn& fn, Event::defaultELFn*& listenerPtr) {
		Event::on(0, 0, eventId, fn, listenerPtr);
	}
	void Event::on(const elemId_t& eventId, const Event::defaultELFn& fn) {
		Event::on(0, 0, eventId, fn);
	}

	void Event::off(const elemId_t& eventId, const defaultELFn& fn) {
		Event::off(0, 0, eventId, fn);
	};
	void Event::off(const elemId_t& eventId, defaultELFn* fn) {
		Event::off(0, 0, eventId, fn);
	};

	void Event::emit(const std::string& eventId, Event::baseEvent* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = 0; tmp[1] = 0; tmp[2] = strHash(eventId.data());
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ e, tmp });
	}
	void Event::emit(const std::string& eventId, void* e) {
		elemId_t* tmp = new elemId_t[3];
		tmp[0] = 0; tmp[1] = 0; tmp[2] = strHash(eventId.data());
		Event::emittsStore.push_back(new Event::mainEmitterPair_t{ new Event::dataEvent(e), tmp });
	}
	void Event::on(const std::string& eventId, const Event::defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr) {
		Event::on(0, 0, strHash(eventId.data()), fn, additionData, listenerPtr);
	}
	void Event::on(const std::string& eventId, const Event::defaultELFn& fn, void* additionData) {
		Event::on(0, 0, strHash(eventId.data()), fn, additionData);
	}
	void Event::on(const std::string& eventId, const Event::defaultELFn& fn, Event::defaultELFn*& listenerPtr) {
		Event::on(0, 0, strHash(eventId.data()), fn, listenerPtr);
	}
	void Event::on(const std::string& eventId, const Event::defaultELFn& fn) {
		Event::on(0, 0, strHash(eventId.data()), fn);
	}

	void Event::off(const std::string& eventId, const defaultELFn& fn) {
		Event::off(0, 0, strHash(eventId.data()), fn);
	};
	void Event::off(const std::string& eventId, defaultELFn* fn) {
		Event::off(0, 0, strHash(eventId.data()), fn);
	};

	void Event::clearRemoved() {
		for (const Event::mainELWindowsPair_t& types : Event::eventListenersRemoverStore) {
			Event::mainELTypes_t* ttmp = Event::eventListenersStore[types.first];
			
			for (const Event::mainELTypesPair_t& elements : *types.second) {
				Event::mainELElementsMap_t* etmp = ttmp->operator[](elements.first);
				for (const Event::mainELElementsPair_t& fns : *elements.second) {

					Event::mainELFnVector_t* ftmp = etmp->operator[](fns.first);

					for (int i = 0; i < ftmp->size(); i++) {
						char** arr = ftmp->operator[](i);
						if (*(bool*)arr[2]) {
							delete[] arr[2];
							delete (Event::defaultELFn*)arr[0];
							ftmp->erase(ftmp->begin() + i);
							delete[] arr;
							i--;
						}
					}
					
					if (ftmp->size() == 0) {
						delete ftmp;
						etmp->erase(fns.first);
					}
				}
				if (etmp->size() == 0) {
					delete etmp;
					ttmp->erase(elements.first);
				}
				delete elements.second;
			}
			if (ttmp->size() == 0) {
				delete ttmp;
				Event::eventListenersStore.erase(types.first);
			}
			delete types.second;
		}
		Event::eventListenersRemoverStore.clear();
	}

	void Event::removeWindow(elemId_t wid) {
		Event::mainELTypes_t* tmpREMtypes;
		Event::mainELTypes_t* tmptypes;
		Event::mainELElementsMap_t* tmpREMelements;

		if (Event::eventListenersStore.find(wid) == Event::eventListenersStore.end())
			return;
		tmptypes = Event::eventListenersStore[wid];

		if (Event::eventListenersRemoverStore.find(wid) == Event::eventListenersRemoverStore.end()) {
			tmpREMtypes = new Event::mainELTypes_t;
			Event::eventListenersRemoverStore[wid] = tmpREMtypes;
		}
		else
			tmpREMtypes = Event::eventListenersRemoverStore[wid];

		for (const Event::mainELTypesPair_t& elements : *tmptypes) {
			if (tmpREMtypes->find(elements.first) == tmpREMtypes->end()) {
				tmpREMelements = new Event::mainELElementsMap_t;
				tmpREMtypes->operator[](elements.first) = tmpREMelements;
			}
			else
				tmpREMelements = tmpREMtypes->operator[](elements.first);

			for (const Event::mainELElementsPair_t& fns : *elements.second) {
				if (tmpREMelements->find(fns.first) == tmpREMelements->end()) {
					tmpREMelements->operator[](fns.first) = nullptr;
				}

				for (char** arr : *fns.second) {
					
					if (*(bool*)arr[2])
						continue;
					*(bool*)arr[2] = 1;
				}
			}
		}
	};

	void Event::removeElement(elemId_t wid, elemId_t eid) {
		Event::mainELTypes_t* tmpREMtypes;
		Event::mainELTypes_t* tmptypes;
		Event::mainELElementsMap_t* tmpREMelements;
		Event::mainELFnVector_t* tmpvec;

		if (Event::eventListenersStore.find(wid) == Event::eventListenersStore.end())
			return;
		tmptypes = Event::eventListenersStore[wid];

		if (Event::eventListenersRemoverStore.find(wid) == Event::eventListenersRemoverStore.end()) {
			tmpREMtypes = new Event::mainELTypes_t;
			Event::eventListenersRemoverStore[wid] = tmpREMtypes;
		}
		else
			tmpREMtypes = Event::eventListenersRemoverStore[wid];

		for (const Event::mainELTypesPair_t& elements : *tmptypes) {
			if (tmpREMtypes->find(elements.first) == tmpREMtypes->end()) {
				tmpREMelements = new Event::mainELElementsMap_t;
				tmpREMtypes->operator[](elements.first) = tmpREMelements;
			}
			else
				tmpREMelements = tmpREMtypes->operator[](elements.first);

			if (elements.second->find(eid) != elements.second->end()) {
				if (tmpREMelements->find(eid) == tmpREMelements->end()) {
					tmpREMelements->operator[](eid) = nullptr;
				}
				tmpvec = elements.second->operator[](eid);
				for (char** arr : *tmpvec) {
					if (*(bool*)arr[2])
						continue;
					*(bool*)arr[2] = 1;
				}
			}
		}
	};

	//executor
	bool Event::allowExecAll = true;
	void Event::execAll() {
		if (!Event::allowExecAll)
			return;
		
		Event::clearRemoved();

		Event::allowExecAll = false;
		size_t curSize = Event::emittsStore.size();
		for (Event::mainEmitterPair_t* tmp : Event::emittsStore) {
			if (tmp->second != nullptr) {
				Event::mainELElementsMap_t* listeners = Event::getListenerMembers(tmp->second[0], tmp->second[2]);
				if (listeners != nullptr) {
					if (tmp->second[1] != 0) {
						Event::mainELElementsMap_t::const_iterator eiter = listeners->find(tmp->second[1]);
						if (eiter != listeners->end()) {
							for (char** arr : *eiter->second) {
								if (*(bool*)arr[2]) {
									continue;
								}
								tmp->first->additionData = (void*)arr[1];
								(*(Event::defaultELFn*)arr[0])(tmp->first);
							}
						}
					}
					else {
						for (const Event::mainELElementsPair_t& ftmp : *listeners) {
							for (char** arr : *ftmp.second) {
								if (*(bool*)arr[2]) {
									continue;
								}
								tmp->first->additionData = (void*)arr[1];
								(*(Event::defaultELFn*)arr[0])(tmp->first);
							}
						}
					}
				}
				delete[] tmp->second;
			}
			if(!tmp->first->isProtected)
				delete tmp->first;
			delete tmp;
		}
		Event::emittsStore.erase(Event::emittsStore.begin(), Event::emittsStore.begin()+curSize);
		Event::allowExecAll = true;
	}

/* init/terminate
=======================================================*/

	void Event::init() {
		Event::on(__EVENT_FRAMEBUFFER_SIZE, Event::emitFramebufferSize);
		Event::on(__EVENT_MOUSE_MOVE, Event::emitMouseMove);
		Event::on(__EVENT_CLOSE, Event::emitClose);
		Event::on(__EVENT_WINDOW_MOUSE_ENTER, Event::emitWindowMouseEnter);
		Event::on(__EVENT_WINDOW_MOUSE_LEAVE, Event::emitWindowMouseLeave);
	}
}