#pragma once

namespace GUI {
	namespace Style {
		enum States {
			plain = 0,
			hover = 1,
			press = 2,

			count = 3,
			mapSize = 2
		};

		enum Parameters {
			absolute,
			relative
		};
	}
}
