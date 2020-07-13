#pragma once
#include "../common.h"
#include <vector>
#include "../Elements/Element.h"
#include <unordered_set>
#include <mutex>

namespace GUI {
	class Container
	{
	public:
		std::recursive_mutex m;
		//base type info =========================
		static const std::type_info* __base_type;
		virtual const std::type_info* __current_type();

		//data =========================

		std::unordered_set<Elements::Element*> elements;

		//constructor =========================
		Container();

		//some methods =========================
		virtual Container* linkElement(Elements::Element* elem);
		virtual Container* unlinkElement(Elements::Element* elem);
		virtual Container* unlinkAll();

		virtual void removeSelf();
		virtual ~Container();
	};
}