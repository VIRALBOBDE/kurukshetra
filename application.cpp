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
#include "headers/common.h"
#include "headers/shader.h"
#include "headers/IBO.h"
#include "headers/texture.h"
#include "headers/renderer.h"

int main()
{
	renderer2D testrenderer(1280, 720, "TESTING KURUKSHETRA");
	cout << "\nsize is : " << sizeof(vertex);
	/*float coordinates [] =
	{
		100.0f, 100.0f,0.0f,0.0f,0.0f,0.0f, 0.0f , 0.0f ,0.0f,
        300.0f, 100.0f,0.0f,0.0f,0.0f,0.0f, 1.0f , 0.0f ,0.0f,
        300.0f, 300.0f,0.0f,0.0f,0.0f,0.0f, 1.0f , 1.0f ,0.0f,
        100.0f, 300.0f,0.0f,0.0f,0.0f,0.0f, 0.0f , 1.0f ,0.0f
	};*/

	/*unsigned int indices[] =
	{
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4
	};

	vertex naya_vertex[4];
	testrenderer.draw_quad({ 0.0f, 0.0f }, { 100.0f,100.0f }, { 1.0f,0.0f,0.0f } , naya_vertex);
	vao firstvao;
	vbo firstvbo(sizeof(naya_vertex)*4000);
	ibo firstibo(indices   , sizeof(indices));
	firstvao.loaddata(0, 2 , 9 , 0 , 0);
	firstvao.loaddata(1, 4 , 9 , 2 , 0);
	firstvao.loaddata(2, 2 , 9 , 6 , 0);
	firstvao.loaddata(3, 1 , 9 , 8 , 0);
	firstvbo.unbind();*/

	/*shader firstshader("resources/shaders/default.shader");
	firstshader.use();
	camera  firstcamera(1280, 720);
	firstshader.setsampler("text", 0);
	              glm::mat4 viewprojectionmatrix = firstcamera.view_projection_matrix();
	firstshader.setsamplermatrix("view_projection", viewprojectionmatrix);
	texture firsttexture ("resources/textures/bheem.jpg" , 0);
	             
	float camera_position[]    = { 0.0f,0.0f,0.0f };
	float objectApos[]         = { 0.0f,0.0f,0.0f };
	glm::mat4 mvp;
	glm::mat4 objectA = glm::translate(glm::mat4(1.0f), glm::vec3(objectApos[0], objectApos[1], objectApos[2]));*/
	testrenderer.set_shader("resources/shaders/default.shader");
	testrenderer.set_texture("resources/textures/bheem.jpg", 0);
	
	while (!testrenderer.is_window_closed())
	{          
		        testrenderer.set_colors(1.0f, 0.0f, 1.0f, 1.0f);
	   //firstcamera.viewmatrix({ camera_position[0],camera_position[1] ,camera_position[2] });
	   //testrenderer.bind_shader();
	   //testrenderer.bind_texture(0);
	   //firstvao.bind();
	        /*testrenderer.bindvao();
            mvp = viewprojectionmatrix * objectA;
            firstshader.setsamplermatrix("view_projection", mvp);*/
	   //firstvbo.bind();
	   //firstvbo.subdata(naya_vertex, sizeof(naya_vertex));
	   //firstibo.bind();
	   //GLcall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
		        testrenderer.Begin_Scene(0);
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						float x = i * 120.0f; // Har cowboy ke beech 120 pixels ka gap
						float y = j * 120.0f;

						// Left-Bottom = {x, y}
						// Right-Top   = {x + 100, y + 100} (Size 100x100)
						testrenderer.draw_quad({ x, y }, { x + 100.0f, y + 100.0f }, { 1.0f, 1.0f, 1.0f });
					}
				}
				float frameTime = ImGui::GetIO().DeltaTime;
				float fps = 1.0f / frameTime;

				// 2. ImGui window mein dikhao
				ImGui::Begin("Engine Stats");
				ImGuiIO& io = ImGui::GetIO();
				ImGui::Text("FPS: %.1f", io.Framerate);
				ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
				ImGui::End();
		        testrenderer.End_Scene();
             	testrenderer.swap_buffers();
		        glfwPollEvents();
	}
	

   return 0;
}