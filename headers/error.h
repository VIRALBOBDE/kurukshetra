#include <glad/glad.h>
#include "iostream"
using namespace std;

#define MY_ASSERT(x) if(!(x)) __debugbreak();
#define GLcall(s) calllog();\
				  s;\
				  MY_ASSERT(geterror(#s,__FILE__,__LINE__))


void calllog();
bool geterror(const char* function, const char* file, int line);