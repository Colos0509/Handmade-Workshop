#pragma once

/*===================================================================#
| 'Grid' source files last updated on 7 July 2021                    |
#===================================================================*/

#include "Buffer.h"
#include "Object.h"
#include "Shader.h"

class Grid : public Object
{

public:

	Grid(GLint size = 15, GLfloat lineWidth = 1.5f);
	virtual ~Grid();

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	GLint m_size;
	Buffer m_buffer;
	GLfloat m_lineWidth;

	const GLuint QUADRANTS = 4;
	const GLuint BYTES_PER_VERTEX = Buffer::ComponentSize::XYZ * sizeof(GLint);
	const GLuint BYTES_PER_COLOR = Buffer::ComponentSize::RGBA * sizeof(GLfloat);

	void Create();

};