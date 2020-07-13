#include "StyleStorage.h"
namespace GUI {
	namespace Style {
		std::mutex StylesStorage::m;

		StyleSet* StylesStorage::set(HashId elementId, States interactState) {
			std::lock_guard<std::mutex> g(StylesStorage::m);
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second->sets + interactState;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t->sets + interactState;
		};

		StyleSetStateMixer* StylesStorage::stateMixer(HashId elementId) {
			std::lock_guard<std::mutex> g(StylesStorage::m);
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t;
		}

		inline StyleSetStateMixer** StylesStorage::createArray(const HashId* begin, const HashId* end, const int size) {
			StyleSetStateMixer** tmp = new StyleSetStateMixer * [size];
			size_t tsize = 0;
			
			list_stylesMap_t::const_iterator cur,
				stylesEnd = StylesStorage::styles.end();

			do {
				end--;
				cur = StylesStorage::styles.find(end->data);
				if (cur == stylesEnd) {
					tmp[tsize] = new StyleSetStateMixer;
					StylesStorage::styles[end->data] = tmp[tsize];
					tsize++;
				}
				else {
					tmp[tsize] = cur->second;
					tsize++;
				}
			} while (end != begin);

			return tmp;
		}

		StyleSetAspectMixer* StylesStorage::aspectMixer(const HashId* begin, const HashId* end, const int size) {
			std::lock_guard<std::mutex> g(StylesStorage::m);
			StyleSetStateMixer** tmp = StylesStorage::createArray(begin, end, size);
			return new StyleSetAspectMixer(tmp, tmp + size);
		}

		StyleSetAspectMixer* StylesStorage::rebuildAspectMixer(StyleSetAspectMixer* mixer, const HashId* begin, const HashId* end, const int size) {
			std::lock_guard<std::mutex> g(StylesStorage::m);
			StyleSetStateMixer** tmp = StylesStorage::createArray(begin, end, size);
			return mixer->resetAspects(tmp, tmp + size);
		};

		StylesStorage::list_stylesMap_t StylesStorage::styles;

		void StylesStorage::terminate() {
			std::lock_guard<std::mutex> g(StylesStorage::m);
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.begin(),
				end = StylesStorage::styles.end();
			for (; cur != end; cur++) {
				delete cur->second;
			}
			StylesStorage::styles.clear();
		}
	}
}