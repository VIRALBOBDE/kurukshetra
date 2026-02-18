#include "headers/error.h"

void calllog()
{
	while (glGetError() != GL_NO_ERROR);
}

bool geterror(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		cout << "\nerror code :" << error << " encountered at\nline no: " << line << " \nin file: " << file << " \nin funciton: " << function << "\n";
		return false;
	}
	return true;
}
