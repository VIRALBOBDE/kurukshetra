#include<headers/window.h>
window::window(int width, int height,  const char* name, int major, int minor)
{
	glfwInit();
	this->height = height;
	this->width = width;
	this->name = name;
	this->major = major;
	this->minor = minor;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	myWindow = glfwCreateWindow(width, height , name, NULL, NULL);
	glfwMakeContextCurrent(myWindow);
	if (glfwGetCurrentContext() == nullptr) {
		std::cout << "CRITICAL ERROR: No OpenGL Context!" << std::endl;
		__debugbreak();
	}
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(myWindow , true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void window::context()
{
	glfwMakeContextCurrent(myWindow);
}

bool window::iswindowclose()
{
	return glfwWindowShouldClose(myWindow);
}

void window::swapbuffer()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(myWindow);
}

bool window::checkwindow()
{
	if (!myWindow)
	{
		std::cout << "couldn't open window.";
		glfwTerminate();
		return false;
	}
	else return true;
}

void window::setcolors(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
