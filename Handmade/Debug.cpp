#include <iostream>
#include "Debug.h"

//get handle on console output window
HANDLE Debug::s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

//======================================================================================================
void Debug::GLError()
{
	//query OpenGL for errors which will return the first 
	//error that occured since this function was last called
	GLenum errorCode = glGetError();

	//based on error code enum type returned output a more friendly error message
	switch (errorCode)
	{

	case GL_NO_ERROR:
	{
		Log("There are no errors.", ErrorCode::SUCCESS);
		break;
	}

	case GL_INVALID_ENUM:
	{
		Log("Invalid enumeration type passed.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_VALUE:
	{
		Log("Numeric value outside of accepted range.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_OPERATION:
	{
		Log("Invalid operation.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_FRAMEBUFFER_OPERATION:
	{
		Log("Framebuffer object incomplete.", ErrorCode::FAILURE);
		break;
	}

	case GL_STACK_OVERFLOW:
	{
		Log("Stack overflow.", ErrorCode::FAILURE);
		break;
	}

	case GL_STACK_UNDERFLOW:
	{
		Log("Stack underflow.", ErrorCode::FAILURE);
		break;
	}

	case GL_OUT_OF_MEMORY:
	{
		Log("Out of memory.", ErrorCode::FAILURE);
		break;
	}

	}
}
//======================================================================================================
void Debug::PauseLog()
{
	system("pause");
}
//======================================================================================================
void Debug::ClearLog()
{
	system("cls");
}
//======================================================================================================
void Debug::DisplayProfile()
{
	Debug::Log("===============================================================");
	Debug::Log("Your graphics card profile is as follows:                      ");
	Debug::Log("===============================================================");

	std::string profile;

	//display the manufacturer of the graphics hardware
	profile = (const char*)(glGetString(GL_VENDOR));
	Debug::Log("Graphics Card Vendor: " + profile);

	//display the make and model of the graphics card
	profile = (const char*)(glGetString(GL_RENDERER));
	Debug::Log("Graphics Card Model: " + profile);

	//display the current OpenGL version and mode set
	profile = (const char*)(glGetString(GL_VERSION));
	Debug::Log("OpenGL Version: " + profile);

	//display which GLSL version is supported by the graphics card
	profile = (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION));
	Debug::Log("GLSL Version: " + profile);

	Debug::Log("===============================================================");
}
//======================================================================================================
void Debug::DisplayExtensions()
{
	//variable to store total amount of supported extensions 
	GLint totalExtensions;

	//get total number of extensions supported by our graphics card
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	Debug::Log("===============================================================");
	Debug::Log("The following extensions are supported by your graphics card:  ");
	Debug::Log("===============================================================");

	//loop through all extensions and display them
	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::string extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
		Debug::Log("Extension #" + std::to_string(i + 1) + ": " + extension);
	}

	Debug::Log("===============================================================");
}
//======================================================================================================
void Debug::Log(GLfloat value, const std::string& label)
{
	//set color to a bright white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

	//display numeric data and if there is a label
	//to identify the data then display that first

	if (!label.empty())
	{
		std::cout << "[" << label << "] ";
	}

	std::cout << value << std::endl;
}
//======================================================================================================
void Debug::Log(const glm::vec3& vector, const std::string& label)
{
	//set color to a bright white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

	//display vector data in coordinate format and if there
	//is a label to identify the data then display that first

	if (!label.empty())
	{
		std::cout << "[" << label << "] ";
	}

	std::cout << "x = " << vector.x << ", y = " << vector.y << ", z = " << vector.z << std::endl;
}
//======================================================================================================
void Debug::Log(const std::string& message, ErrorCode errorCode)
{
	//set color based on the numeric error code passed
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(errorCode));

	//display the message on the console
	std::cout << message << std::endl;

	//set color back to a bright white so that if the
	//text is output elsewhere it will be regular white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));
}
//======================================================================================================
void Debug::Log(GLfloat x, GLfloat y, GLfloat z, const std::string& label)
{
	//set color to a bright white
	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));

	//display vector data in coordinate format and if there
	//is a label to identify the data then display that first

	if (!label.empty())
	{
		std::cout << "[" << label << "] ";
	}

	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}