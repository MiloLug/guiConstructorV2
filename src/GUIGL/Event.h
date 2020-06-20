#pragma once
#ifndef __GUIGL_EVENT

#define __GUIGL_EVENT

#include "common.h"
#include <functional>
#include <stack>
#include <map>
#include <vector>
#include <string>

//dev
#define __EVENT_FRAMEBUFFER_SIZE	18115106642343686001
#define __EVENT_MOUSE_MOVE			16513634541740518575
#define __EVENT_CLOSE				14389682063295320816
#define __EVENT_WINDOW_MOUSE_ENTER	7168051084191190288
#define __EVENT_WINDOW_MOUSE_LEAVE	7993607447241117450
#define __EVENT_MOUSE_DOWN			8745836582348529421
#define __EVENT_MOUSE_UP			1864734245079309702

//user
#define EVENT_FRAMEBUFFER_SIZE		9092443765447460580
#define EVENT_MOUSE_MOVE			10337664012170136903
#define EVENT_CLOSE					1780671892284384638
#define EVENT_WINDOW_MOUSE_ENTER	1065488583578954144
#define EVENT_WINDOW_MOUSE_LEAVE	4815796777779257801
#define EVENT_MOUSE_DOWN			2700025637071978721
#define EVENT_MOUSE_UP				8774351539683433295


namespace GUI {
	class Event
	{
	public:
		class baseEvent;

		typedef std::function<void(baseEvent*)> defaultELFn;

		typedef std::pair<baseEvent*, elemId_t*> mainEmitterPair_t;

		typedef std::map<elemId_t, defaultELFn*> mainEmittersMap_t;

		typedef std::vector<char**> mainELFnVector_t;
		typedef std::pair<elemId_t, mainELFnVector_t*> mainELElementsPair_t;
		typedef std::map<elemId_t, mainELFnVector_t*> mainELElementsMap_t;
		typedef std::map<elemId_t, mainELElementsMap_t*> mainELTypes_t;
		typedef std::pair<elemId_t, mainELElementsMap_t*> mainELTypesPair_t;
		typedef std::map<elemId_t, mainELTypes_t*> mainELWindowsMap_t;
		typedef std::pair<elemId_t, mainELTypes_t*> mainELWindowsPair_t;
/* main event types
=======================================================*/
		class baseEvent {
		public:
			elemId_t window = 0;
			elemId_t element = 0;
			elemId_t topElelemt = 0;
			bool isProtected = false;
			void* data = nullptr;
			void* additionData = nullptr;
			elemId_t eventId = 0;
			baseEvent() = default;
			baseEvent(bool isProtected);
			baseEvent(const baseEvent&);
			virtual ~baseEvent();
		};

		class dataEvent : public baseEvent {
		public:
			dataEvent() = default;
			dataEvent(void* data);
			dataEvent(const dataEvent&);
			virtual ~dataEvent();
		};

		class framebufferSizeEvent : public baseEvent {
		public:
			int width;
			int height;

			framebufferSizeEvent(int width, int height);
			framebufferSizeEvent(const framebufferSizeEvent&);
			virtual ~framebufferSizeEvent();
		};

		class mouseMoveEvent : public baseEvent {
		public:
			double X = 0;
			double Y = 0;

			mouseMoveEvent(double X, double Y);
			mouseMoveEvent(const mouseMoveEvent&);
			virtual ~mouseMoveEvent();
		};

		class mouseButtonEvent : public baseEvent {
		public:
			double X = 0;
			double Y = 0;
			unsigned short int button = 0;

			mouseButtonEvent(double X, double Y, unsigned short int button);
			mouseButtonEvent(const mouseButtonEvent&);
			virtual ~mouseButtonEvent();
		};

		class closeEvent : public baseEvent {
		public:
			closeEvent() = default;
			closeEvent(const closeEvent&);
			virtual ~closeEvent();
		};

		class windowMouseEnterEvent : public baseEvent {
		public:
			windowMouseEnterEvent() = default;
			windowMouseEnterEvent(const windowMouseEnterEvent&);
			virtual ~windowMouseEnterEvent();
		};

		class windowMouseLeaveEvent : public baseEvent {
		public:
			windowMouseLeaveEvent() = default;
			windowMouseLeaveEvent(const windowMouseLeaveEvent&);
			virtual ~windowMouseLeaveEvent();
		};

/* process
=======================================================*/
		static mainELElementsMap_t* getListenerMembers(elemId_t wid, elemId_t eventId);

		//main events emitters
		static void emitFramebufferSize(baseEvent* e);
		static void emitMouseMove(baseEvent* e);
		static void emitClose(baseEvent* e);
		static void emitWindowMouseEnter(baseEvent* e);
		static void emitWindowMouseLeave(baseEvent* e);

		//main events emitters
		static std::vector<mainEmitterPair_t*> emittsStore;
		static mainELWindowsMap_t eventListenersStore;
		static mainELWindowsMap_t eventListenersRemoverStore;

		//window plain emitter
		/*static void emit(elemId_t wid, elemId_t eid, const elemId_t& eventId);
		static void emit(elemId_t wid, elemId_t eid, const elemId_t& eventId);

		static void emit(elemId_t wid, const elemId_t& eventId);
		static void emit(elemId_t wid, const elemId_t& eventId);*/

		static void emit(elemId_t wid, elemId_t eid, const elemId_t& eventId, baseEvent* e);
		static void emit(elemId_t wid, elemId_t eid, const elemId_t& eventId, void* e = nullptr);

		static void emit(elemId_t wid, const elemId_t& eventId, baseEvent* e);
		static void emit(elemId_t wid, const elemId_t& eventId, void* e = nullptr);
		
		static void on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const defaultELFn& fn, void *additionData, Event::defaultELFn*& listenerPtr);
		static void on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const defaultELFn& fn, void* additionData);
		static void on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const defaultELFn& fn, Event::defaultELFn*& listenerPtr);
		static void on(elemId_t wid, elemId_t eid, const elemId_t& eventId, const defaultELFn& fn);

		static void addRemover(elemId_t wid, elemId_t eid, const elemId_t& eventId);

		static void off(elemId_t wid, elemId_t eid, const elemId_t& eventId, const defaultELFn& fn);
		static void off(elemId_t wid, elemId_t eid, const elemId_t& eventId, defaultELFn *fn);

		//root emitter
		static void emit(const elemId_t& eventId, baseEvent* e);
		static void emit(const elemId_t& eventId, void* e = nullptr);
		
		static void on(const elemId_t& eventId, const defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr);
		static void on(const elemId_t& eventId, const defaultELFn& fn, void* additionData);
		static void on(const elemId_t& eventId, const defaultELFn& fn, Event::defaultELFn*& listenerPtr);
		static void on(const elemId_t& eventId, const defaultELFn& fn);

		static void off(const elemId_t& eventId, const defaultELFn& fn);
		static void off(const elemId_t& eventId, defaultELFn* fn);

		static void emit(const std::string& eventId, baseEvent* e);
		static void emit(const std::string& eventId, void* e = nullptr);
		
		static void on(const std::string& eventId, const defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr);
		static void on(const std::string& eventId, const defaultELFn& fn, void* additionData);
		static void on(const std::string& eventId, const defaultELFn& fn, Event::defaultELFn*& listenerPtr);
		static void on(const std::string& eventId, const defaultELFn& fn);

		static void off(const std::string& eventId, const defaultELFn& fn);
		static void off(const std::string& eventId, defaultELFn* fn);

		//static void emit(elemId_t wid, elemId_t eid, std::string eventName, void* e);
	
		static void clearRemoved();

		static void removeWindow(elemId_t wid);
		static void removeElement(elemId_t wid, elemId_t eid);

		//executor
		static bool allowExecAll;
		static void execAll();
/* init/terminate
=======================================================*/
		//static void terminate();
		static void init();
	};
}

#endif