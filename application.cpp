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
	renderer2D testrenderer(1280, 720, "KURUKSHETRA TEST ENGINE");
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
	testrenderer.set_texture("resources/textures/ideal_bheem.png", 0);
	float screen_colors[4] = {0,0,0,1 };
	float frameTimer = 0.0f; // Har frame ka time jodega
	float frameDelay = 0.05f; // Kitni der ek frame dikhega (in seconds)
	int j = 0;
	int direction = 1; // 1 matlab aage jaao, -1 matlab peeche
	float timer = 0.0f;
	float delay = 0.12f;
	while (!testrenderer.is_window_closed())
	{          
		        testrenderer.set_colors(screen_colors[0], screen_colors[1], screen_colors[2], screen_colors[3]);
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
					//for (int i = 0; i < 10; i++)
					//{
					//	for (int j = 0; j < 10; j++)
					//	{
					//		float x = i * 120.0f; // Har cowboy ke beech 120 pixels ka gap
					//		float y = j * 120.0f;

					//		// Left-Bottom = {x, y}
					//		// Right-Top   = {x + 100, y + 100} (Size 100x100)
					//		testrenderer.draw_quad({ x, y }, { x + 100.0f, y + 100.0f }, { 1.0f, 1.0f, 1.0f });
					//	}
					//}
					float deltaTime = ImGui::GetIO().DeltaTime; // Engine ka frame time
					frameTimer += deltaTime;

					// Agar time target se upar gaya, toh frame badhao
					

					// Loop ke andar
					timer += deltaTime;

					if (timer >= delay) {
						j += direction; // Direction ke hisaab se j ko badhao ya ghatao

						// Boundary Check
						if (j >= 5) {
							direction = -1; // End pe pahunche, ab wapas mudho
						}
						else if (j <= 0) {
							direction = 1;  // Shuruat pe pahunche, ab aage badho
						}

						timer = 0.0f;
					}
					testrenderer.draw_quad({ 30, 200 }, { 200.0f, 400.0f }, { 0.0f, 0.0f, 0.0f }, {(float) j,0 });
					float frameTime = ImGui::GetIO().DeltaTime;
					float fps = 1.0f / frameTime;

					// ImGui rendering
					ImGui::Begin("Engine Stats");
					ImGuiIO& io = ImGui::GetIO();
					ImGui::Text("FPS: %.1f", io.Framerate);
					ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
					ImGui::ColorEdit4("Background Color", screen_colors);
					ImGui::End();

					//done drawing
					testrenderer.End_Scene();
					//testrenderer.swap_buffers();
		        
	}
	

   return 0;
}