#include "VAO.h"

namespace GUI {
	VAO::VAO() {
		glGenVertexArrays(1, &this->vaoid);
		this->bind();
	}

	void VAO::bind() {
		glBindVertexArray(this->vaoid);
	}

	void VAO::draw(GLsizei count) {
		this->bind();
		for (unsigned short int i = 0; i < this->vbocount; ++i)
		{
			glEnableVertexAttribArray(i);
		}
		glDrawArrays(GL_QUADS, 0, count);
		for (unsigned short int i = 0; i < this->vbocount; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void VAO::addVBO(const std::vector<float>& data) {
		glGenBuffers(1, this->vboid + this->vbocount);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboid[this->vbocount]);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
		this->vbocount++;
	}

	VAO::~VAO() {
		glDeleteBuffers(this->vbocount, this->vboid);
		glDeleteVertexArrays(1, &this->vaoid);
	}
}