#include "StyleSetStateMixer.h"

#define GUIGL_STYLE_stateGetter(_name_) \
StyleSetStateMixer::_name_(bool* interactState) {\
	return (this->sets + (\
	interactState[GUI::Style::States::press - 1] && (this->sets + GUI::Style::States::press)->_##_name_##Set\
	? GUI::Style::States::press\
	: interactState[GUI::Style::States::hover - 1] && (this->sets + GUI::Style::States::hover)->_##_name_##Set\
		? GUI::Style::States::hover\
		: GUI::Style::States::plain\
	))->_##_name_;\
}\
bool StyleSetStateMixer::_name_##Set(bool* interactState) {\
	return (interactState[GUI::Style::States::press - 1] && (this->sets + GUI::Style::States::press)->_##_name_##Set)\
		|| (interactState[GUI::Style::States::hover - 1] && (this->sets + GUI::Style::States::hover)->_##_name_##Set)\
		|| this->sets->_##_name_##Set;\
}

namespace GUI {
	namespace Style {
		void StyleSetStateMixer::removeSelf() {
			delete this;
		}
		StyleSetStateMixer::~StyleSetStateMixer() {}

		int GUIGL_STYLE_stateGetter(width)
		int GUIGL_STYLE_stateGetter(height)
		int GUIGL_STYLE_stateGetter(left)
		int GUIGL_STYLE_stateGetter(top)
		int GUIGL_STYLE_stateGetter(zIndex)
		Parameters GUIGL_STYLE_stateGetter(position)
	}
}