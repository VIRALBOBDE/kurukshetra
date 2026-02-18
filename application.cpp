#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>

#include "headers/window.h"
#include "headers/VBO.h"
#include "headers/VAO.h"
#include "headers/camera.h"
#include "headers/shader.h"
#include "headers/IBO.h"
#include "headers/texture.h"

int main()
{
	window gamewindow(1280,720,"kurukshetra engine",3,3);
	gamewindow.checkwindow();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	float coordinates [] =
	{
		100.0f, 100.0f, 0.0f , 0.0f ,
        300.0f, 100.0f, 1.0f , 0.0f ,
        300.0f, 300.0f, 1.0f , 1.0f ,
        100.0f, 300.0f, 0.0f , 1.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};

	vao firstvao;
	vbo firstvbo(coordinates , sizeof(coordinates));
	ibo firstibo(indices     , sizeof(indices));
	firstvao.loaddata(0, 2 , 4 , 0 , 0);
	firstvao.loaddata(1, 2 , 4 , 2 , 0);
	firstvbo.unbind();
	shader firstshader("resources/shaders/default.shader");
	firstshader.use();
	camera  firstcamera(1280, 720);
	firstshader.setsampler("text", 0);
	              glm::mat4 viewprojectionmatrix = firstcamera.view_projection_matrix();
	firstshader.setsamplermatrix("view_projection", viewprojectionmatrix);
	texture firsttexture ("resources/textures/bheem.jpg" , 0);
	             
	float camera_position[]    = { 0.0f,0.0f,0.0f };
	float objectApos[]         = { 0.0f,0.0f,0.0f };
	glm::mat4 mvp;
	glm::mat4 objectA = glm::translate(glm::mat4(1.0f), glm::vec3(objectApos[0], objectApos[1], objectApos[2]));
	while (!gamewindow.iswindowclose())
	{          
		gamewindow.setcolors(1.0f, 0.5f, 0.4f, 1.0f);
		firstcamera.viewmatrix({ camera_position[0],camera_position[1] ,camera_position[2] });
		firstshader.use();
		firsttexture.bind(0);
		firstvao.bind();
        mvp = viewprojectionmatrix * objectA;
	    firstshader.setsamplermatrix("view_projection", mvp);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		gamewindow.swapbuffer();
		glfwPollEvents();
	}

   return 0;
}