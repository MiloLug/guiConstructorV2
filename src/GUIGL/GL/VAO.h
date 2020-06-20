#pragma once
#include <vector>
#include "../glall.h"

namespace GUI {
	class VAO
	{
	private:
		GLuint vaoid;
		GLuint vboid[16];
		unsigned short int vbocount = 0;
	public:
		VAO();
		void draw(GLsizei count);
		void bind();
		void addVBO(const std::vector<float>& data);
		~VAO();
	};
}