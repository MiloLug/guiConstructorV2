#pragma once
#include "constants.h"

namespace GUI {
	namespace Style {
		class StyleSet {
		public:
			virtual void removeSelf();
			virtual ~StyleSet();

			int _width = 0;
			bool _widthSet = false;

			int _height = 0;
			bool _heightSet = false;
			
			int _left = 0;
			bool _leftSet = false;
			
			int _top = 0;
			bool _topSet = false;
			
			int _zIndex = 0;
			bool _zIndexSet = false;

			Parameters _position = Parameters::relative;
			bool _positionSet = false;


			virtual int width();
			virtual StyleSet* width(int t);

			virtual int height();
			virtual StyleSet* height(int t);

			virtual int left();
			virtual StyleSet* left(int t);

			virtual int top();
			virtual StyleSet* top(int t);

			virtual int zIndex();
			virtual StyleSet* zIndex(int t);

			virtual Parameters position();
			virtual StyleSet* position(Parameters t);
		};
	}
}
