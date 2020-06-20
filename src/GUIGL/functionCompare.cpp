#include "functionCompare.h"

namespace GUI {
	template<typename T, typename... U>
	bool fnCanBeCompared(const std::function<T(U...)>& f) {
		typedef T(fnType)(U...);
		fnType* const* fnPointer = f.template target<fnType*>();
		return fnPointer != nullptr;
	}

	template<typename T, typename... U>
	bool fnEquals(const std::function<T(U...)>& f1, const std::function<T(U...)>& f2) {
		typedef T(fnType)(U...);
		fnType* const* fnPointer1 = f1.template target<fnType*>();
		fnType* const* fnPointer2 = f2.template target<fnType*>();
		return fnPointer1 != nullptr
			&& fnPointer2 != nullptr
			&& *fnPointer1 == *fnPointer2;
	}
}