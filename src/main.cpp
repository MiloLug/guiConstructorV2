#include <iostream>
#include <string>
#include <GUIGL/Elements/Elements.h>
#include <Math.h>

using namespace GUI;
using namespace GUI::Elements;

int main() {
	
	Window* kek = new Window;

	kek->addElement(new Element);

	std::cout << kek->elements.size();

	return 0;
}