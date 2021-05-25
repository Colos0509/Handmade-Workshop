#include <iostream>
#include "Buffer.h"
#include "Debug.h"
#include "Shader.h"

//this allocated space remains in memory until the application ends
std::map<std::string, BufferID>* Buffer::s_bufferIDMap = new std::map<std::string, BufferID>;

//======================================================================================================
void Buffer::Output()
{
	//clear the console window for a fresh display
	Debug::ClearLog();

	//display total amount of buffer IDs stored in map
	Debug::Log("===============================================================");
	Debug::Log("Size of Buffer ID Map: " + std::to_string(s_bufferIDMap->size()));
	Debug::Log("===============================================================");

	//loop through map and display each buffer detailing its OpenGL IDs and tag name
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{

		Debug::Log(it->first);
		Debug::Log("---------------------------------------------------------------");

		Debug::Log((GLfloat)it->second.vaoID, "VAO ID");
		Debug::Log((GLfloat)it->second.vboID[VERTEX_BUFFER], "VERTEX VBO ID");
		Debug::Log((GLfloat)it->second.vboID[COLOR_BUFFER], "COLOR VBO ID");
		Debug::Log((GLfloat)it->second.vboID[NORMAL_BUFFER], "NORMAL VBO ID");
		Debug::Log((GLfloat)it->second.vboID[TEXTURE_BUFFER], "TEXTURE VBO ID");
		Debug::Log((GLfloat)it->second.eboID, "EBO ID");

		(it->second.hasEBO) ? Debug::Log("This buffer has an EBO")
			: Debug::Log("This buffer has no EBO");

		Debug::Log((GLfloat)it->second.totalVertices, "Total vertices");
		Debug::Log("===============================================================");

	}
}
//======================================================================================================
Buffer::Buffer()
{
	m_ID.vaoID = 0;
	m_ID.eboID = 0;
	m_ID.vboID[VERTEX_BUFFER] = 0;
	m_ID.vboID[COLOR_BUFFER] = 0;
	m_ID.vboID[NORMAL_BUFFER] = 0;
	m_ID.vboID[TEXTURE_BUFFER] = 0;

	m_ID.hasEBO = false;
	m_ID.totalVertices = 0;
}
//======================================================================================================
void Buffer::SetBuffers(const std::string& bufferID)
{
	Debug::Log("Setting buffers to: '" + bufferID + "'");

	//first check if buffer ID exists in map and if not display
	//error message, otherwise go ahead and assign the buffer ID

	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		Debug::Log("Buffer IDs not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		m_ID = it->second;
		Debug::Log("Buffer IDs assigned successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");
	}
}
//======================================================================================================
bool Buffer::CreateBuffers(const std::string& bufferID, GLsizei totalVertices, bool hasEBO)
{
	Debug::Log("Creating buffers in graphics memory: '" + bufferID + "'");

	//first check if buffer ID exists in map and if it does display error message
	//and halt creation because we don't want to replace the existing buffers
	if (s_bufferIDMap->find(bufferID) != s_bufferIDMap->end())
	{
		Debug::Log("Buffers already created in graphics memory.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	//otherwise go ahead and create an ID for the VAO, VBOs and EBO and store in map

	glGenVertexArrays(1, &m_ID.vaoID);
	glGenBuffers(4, m_ID.vboID);
	glGenBuffers(1, &m_ID.eboID);

	m_ID.hasEBO = hasEBO;
	m_ID.totalVertices = totalVertices;

	(*s_bufferIDMap)[bufferID] = m_ID;

	Debug::Log("Buffers created successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;
}
//======================================================================================================
void Buffer::BindEBO()
{
	glBindVertexArray(m_ID.vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);
	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::BindVBO(VBOType vboType, const std::string& vertAttrib,
	ComponentSize componentSize, DataType dataType)
{
	//bind VAO with either the vertex, color, normal or texture VBO
	//here we also link the VBOs with their respective shader attributes
	glBindVertexArray(m_ID.vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glVertexAttribPointer(Shader::Instance()->GetAttributeID(vertAttrib),
		componentSize, dataType, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::Instance()->GetAttributeID(vertAttrib));

	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::FillEBO(const GLuint* data, GLsizeiptr size, FillType fillType)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, fillType);
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLint* data, GLsizeiptr size, FillType fillType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferData(GL_ARRAY_BUFFER, size, data, fillType);
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, FillType fillType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferData(GL_ARRAY_BUFFER, size, data, fillType);
}
//======================================================================================================
void Buffer::FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, FillType fillType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferData(GL_ARRAY_BUFFER, size, data, fillType);
}
//======================================================================================================---
void Buffer::AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID.eboID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID.vboID[vboType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//======================================================================================================
void Buffer::Draw(DrawMode drawMode)
{
	//bind VAO and render everything based on if there are indices or not
	glBindVertexArray(m_ID.vaoID);

	(m_ID.hasEBO) ? glDrawElements(drawMode, m_ID.totalVertices, GL_UNSIGNED_INT, 0)
		: glDrawArrays(drawMode, 0, m_ID.totalVertices);

	glBindVertexArray(0);
}
//======================================================================================================
void Buffer::DestroyBuffers()
{
	Debug::Log("Unloading all buffers from memory...");

	//loop through entire buffer map in order to remove all buffer IDs
	for (auto it = s_bufferIDMap->begin(); it != s_bufferIDMap->end(); it++)
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));
	}

	//clear the buffer ID map
	s_bufferIDMap->clear();

	Debug::Log("Buffers unloaded successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");
}
//======================================================================================================
void Buffer::DestroyBuffers(const std::string& bufferID)
{
	Debug::Log("Unloading buffers: '" + bufferID + "'");

	//check if buffer ID exists in map and if not display error message
	//otherwise remove that specific buffer ID and remove map element
	auto it = s_bufferIDMap->find(bufferID);

	if (it == s_bufferIDMap->end())
	{
		Debug::Log("Buffer IDs not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		glDeleteVertexArrays(1, &(it->second.vaoID));
		glDeleteBuffers(4, it->second.vboID);
		glDeleteBuffers(1, &(it->second.eboID));

		s_bufferIDMap->erase(it);

		Debug::Log("Buffers unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");
	}
}