#pragma once
#include "../common.h"
#include <functional>
#include <string>
#include "../Components/Event/Emitter.h"
#include <unordered_set>
#include <mutex>
#include "../Components/CoordMap.h"
#include "../Components/Style/StyleSetElement.h"
#include "../Components/ClassName/ClassName.h"

namespace GUI {
	class Container;
	namespace Event {
		class DataPack;
	}
	namespace Elements {
		class Window;

		class Element : public Event::Emitter
		{
		public:
			std::recursive_mutex m;

			//base type info =========================
			static const std::type_info* __base_type;
			virtual const std::type_info* __current_type();

			//attributes =========================
			bool _shown = true;
			std::string _title = "";

			std::string title(); //get
			Element* title(const std::string& title); //set

			ClassName::NameContainer* className;

			//elemId_t id = 0; //todo

//data =========================
			std::unordered_set<Container*> containers;
			Window* _parentWindow = nullptr;
			Element* _parent = nullptr;
			CoordPath _coordPath;

			inline virtual Window* parentWindow();
			inline virtual Element* parent();
			inline virtual Element* parentWindow(Window* w);
			inline virtual Element* parentWindowForceMove(Window* w);
			inline virtual Element* parent(Element* el);

			Style::StyleSetElement *style;

			//constructor =========================
			Element();
			Element(const Element& elem) = delete;
			Element(const Element* elem) = delete;

			//some methods =========================
			virtual void __drawBase(int wwidth, int wheight);

			/*Element* windowReviewZ();
			Element* windowRedraw();*/

			virtual Element* hide(); //todo
			virtual Element* show(); //todo

			/*virtual Element* emit(const elemId_t& eventId, Event::baseEvent* e);
			virtual Element* emit(const elemId_t& eventId, void* e = nullptr);

			virtual Element* on(const elemId_t& eventId, const Event::defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr);
			virtual Element* on(const elemId_t& eventId, const Event::defaultELFn& fn, void* additionData);
			virtual Element* on(const elemId_t& eventId, const Event::defaultELFn& fn, Event::defaultELFn*& listenerPtr);
			virtual Element* on(const elemId_t& eventId, const Event::defaultELFn& fn);

			virtual Element* off(const elemId_t& eventId, const Event::defaultELFn& fn);
			virtual Element* off(const elemId_t& eventId, Event::defaultELFn* fn);

			virtual Element* emit(const std::string& eventId, Event::baseEvent* e);
			virtual Element* emit(const std::string& eventId, void* e = nullptr);

			virtual Element* on(const std::string& eventId, const Event::defaultELFn& fn, void* additionData, Event::defaultELFn*& listenerPtr);
			virtual Element* on(const std::string& eventId, const Event::defaultELFn& fn, void* additionData);
			virtual Element* on(const std::string& eventId, const Event::defaultELFn& fn, Event::defaultELFn*& listenerPtr);
			virtual Element* on(const std::string& eventId, const Event::defaultELFn& fn);

			virtual Element* off(const std::string& eventId, const Event::defaultELFn& fn);
			virtual Element* off(const std::string& eventId, Event::defaultELFn* fn);*/

			inline virtual Element* __linkContainer(Container* cont);
			inline virtual Element* __unlinkContainer(Container* cont);
			inline virtual size_t __containersCount();

			inline virtual Element* __updateHeight();

			inline virtual Element* __updateWidth();

			inline virtual Element* __updateLeft();

			inline virtual Element* __updateTop();

			inline virtual Element* __updateZ();

			inline virtual Element* __updatePos();

			inline virtual Element* emit(HashId id, Event::DataPack* data = nullptr, bool propagation = true);

			virtual void removeSelf();
			virtual ~Element();
		};
	}
}