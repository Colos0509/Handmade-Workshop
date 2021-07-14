#include "Grid.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
Grid::Grid(GLint size, GLfloat lineWidth)
{
	m_size = size;
	m_lineWidth = lineWidth;
	Create();
}
//======================================================================================================
Grid::~Grid()
{
	m_buffer.Destroy();
}
//======================================================================================================
void Grid::SetSize(GLint size)
{
	m_size = size;
	m_size = std::max(m_size, 1);
	Create();
}
//======================================================================================================
void Grid::SetLineWidth(GLfloat lineWidth)
{
	m_lineWidth = lineWidth;
}
//======================================================================================================
void Grid::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLuint offset = 0;

	for (int i = 0; i < m_size * QUADRANTS; i++)
	{
		GLfloat colors[] = { r, g, b, a, r, g, b, a };

		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
		offset += sizeof(colors);
	}
}
//======================================================================================================
void Grid::Render(Shader& shader)
{
	Buffer::SetLineWidth(m_lineWidth);

	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::INT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.Render(Buffer::LINES);
}
//======================================================================================================
void Grid::Create()
{
	//We need to add an extra line to close the grid 
	//Each line has two vertex and two color groups
	const GLuint TOTAL_BYTES_VERTEX_VBO = (m_size + 1) * QUADRANTS * BYTES_PER_VERTEX * 2;
	const GLuint TOTAL_BYTES_COLOR_VBO = (m_size + 1) * QUADRANTS * BYTES_PER_COLOR * 2;

	//We don't want to create new buffer 
	//objects everytime the grid is resized
	if (!m_buffer.GetTag().empty())
	{
		m_buffer.Destroy();		
	}

	//We multiply by 2 to represent each line's vertex 
	//and add 4 for the two extra lines to close the grid
	m_buffer.Create("Grid", (m_size * QUADRANTS * 2) + 4);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER,
		static_cast<GLfloat*>(nullptr), TOTAL_BYTES_VERTEX_VBO, Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER,
		static_cast<GLfloat*>(nullptr), TOTAL_BYTES_COLOR_VBO, Buffer::FILL_ONCE);

	GLuint offsetColor = 0;
	GLuint offsetVertex = 0;

	//==================================
	//Negative vertical lines
	//==================================

	for (int i = 0; i <= m_size; i++)
	{
		GLint vertices[] = { -m_size + i, 0,  m_size,      //first vertex
							 -m_size + i, 0, -m_size };    //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Positive vertical lines
	//==================================

	for (int i = 1; i < m_size + 1; i++)
	{
		GLint vertices[] = { 0 + i, 0,  m_size,      //first vertex
							 0 + i, 0, -m_size };    //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Negative horizontal lines
	//==================================

	for (int i = 0; i <= m_size; i++)
	{
		GLint vertices[] = { -m_size, 0, -m_size + i,        //first vertex
							  m_size, 0, -m_size + i };     //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Positive horizontal lines
	//==================================

	for (int i = 1; i < m_size + 1; i++)
	{
		GLint vertices[] = { -m_size, 0, 0 + i,     //first vertex
							  m_size, 0, 0 + i };     //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}
}