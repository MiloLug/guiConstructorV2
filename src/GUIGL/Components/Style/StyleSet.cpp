#include "StyleSet.h"
#include "constants.h"

#define GUIGL_STYLE_styleSetGetterSetter(_name_, _stype_) \
StyleSet::_name_() {\
	return this->_##_name_;\
}\
StyleSet* StyleSet::_name_(_stype_ t) {\
	this->_##_name_ = t;\
	this->_##_name_##Set = true;\
	return this;\
}

namespace GUI {
	namespace Style {
		//style set
		void StyleSet::removeSelf() {
			delete this;
		}
		StyleSet::~StyleSet() {}

		int GUIGL_STYLE_styleSetGetterSetter(width, int)
		int GUIGL_STYLE_styleSetGetterSetter(height, int)
		int GUIGL_STYLE_styleSetGetterSetter(left, int)
		int GUIGL_STYLE_styleSetGetterSetter(top, int)
		int GUIGL_STYLE_styleSetGetterSetter(zIndex, int)
		Parameters GUIGL_STYLE_styleSetGetterSetter(position, Parameters)
	}
}