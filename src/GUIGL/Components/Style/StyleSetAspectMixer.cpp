#include "StyleSetAspectMixer.h"

#define GUIGL_STYLE_aspectGetter(_name_) \
StyleSetAspectMixer::_name_(bool* interactState) {\
	for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {\
		if ((*s)->_name_##Set(interactState)) {\
			return (*s)->_name_(interactState);\
		}\
	}\
	return this->_##_name_;\
}

namespace GUI {
	namespace Style {
		void StyleSetAspectMixer::removeSelf() {
			delete this;
		}
		StyleSetAspectMixer::~StyleSetAspectMixer() {
			if (this->sets != nullptr)
				delete[] this->sets;
		}

		StyleSetAspectMixer* StyleSetAspectMixer::resetAspects(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd) {
			if (this->sets != nullptr)
				delete[] this->sets;
			this->sets = sets;
			this->setsEnd = setsEnd;
			return this;
		}

		StyleSetAspectMixer::StyleSetAspectMixer(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd) : StyleSet() {
			this->sets = sets;
			this->setsEnd = setsEnd;
		}

		int GUIGL_STYLE_aspectGetter(width)
		int GUIGL_STYLE_aspectGetter(height)
		int GUIGL_STYLE_aspectGetter(left)
		int GUIGL_STYLE_aspectGetter(top)
		int GUIGL_STYLE_aspectGetter(zIndex)
		Parameters GUIGL_STYLE_aspectGetter(position)
	}
}