#pragma once
#include <functional>

namespace GUI {
	template<typename T, typename... U>
	bool fnCanBeCompared(const std::function<T(U...)>& f);

	template<typename T, typename... U>
	bool fnEquals(const std::function<T(U...)>& f1, const std::function<T(U...)>& f2);
}