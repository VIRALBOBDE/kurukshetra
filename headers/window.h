#pragma once
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include<iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
class window
{
private:
	const char* name = "window";
	GLFWwindow* myWindow = 0;
	int major = 0, minor = 0;
	int height = 0;
	int width = 0;
	bool shared = 0;
	bool fullscreen = 0;
public:
	window() {}
	window(int height, int width, const char* name, int major, int minor);
	GLFWwindow* windowadd() { return myWindow; }
	void context();
	bool iswindowclose();
	void swapbuffer();
	bool checkwindow();
	void setcolors(float r, float g, float b, float a);
	~window() { glfwTerminate(); }
};