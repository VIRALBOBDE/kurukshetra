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

//the following header files are not completed yet 
#include "to be tested/box.h"
#include "to be tested/Character.h"
#include "to be tested/circular character.h"
#include "to be tested/Circle.h"
#include "to be tested/InputHandling.h"
#include "to be tested/moves.h"
#include "to be tested/physics.h"


int main()
{
	renderer2D testrenderer(1280, 720, "KURUKSHETRA TEST ENGINE");
	cout << "\nsize is : " << sizeof(vertex);
	
	testrenderer.set_shader("resources/shaders/default.shader");
	testrenderer.set_texture("resources/textures/ideal_bheem.png", 0 , 372, 530);
	BoxCharacter Bheem(testrenderer.window_address(), 30.0f, 40.0f, 150.0f, 150.0f);
	BoxCharacter Duryodhan(testrenderer.window_address() ,640.0f, 40.0f, 150.0f, 150.0f);
	//Character Bheem(30.0f, 40.0f, 150.0f);
	//Character Duryodhan(640.0f, 360.0f, 150.0f);
	InputHandler testhandler;
	testhandler.setspeed(.5f);
	//testrenderer.set_texture("resources/textures/slot0.png", 1 , 372, 530);
	float screen_colors[4] = {0,1,0,1 };
	float frameTimer = 0.0f; // Har frame ka time jodega
	float frameDelay = 0.05f; // Kitni der ek frame dikhega (in seconds)
	int j = 0;
	int direction = 1; // 1 matlab aage jaao, -1 matlab peeche
	float timer = 0.0f;
	float delay = 0.12f;
	while (!testrenderer.is_window_closed())
	{          
		Bheem.ApplyPhysics(Duryodhan);
		//Duryodhan.ApplyPhysics(Bheem);
		Bheem.death();
		Duryodhan.death();
		testhandler.ProcessInput(testrenderer.window_address(), Bheem, Duryodhan , testhandler);
		
		            //testrenderer.processinput();
		testrenderer.set_colors(screen_colors[0], screen_colors[1], screen_colors[2], screen_colors[3]);
	   
				
		testrenderer.Begin_Scene(0);
					
					float deltaTime = ImGui::GetIO().DeltaTime; // Engine ka frame time
					frameTimer += deltaTime;

				
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
					testrenderer.draw_quad({ Bheem.body.x, Bheem.body.y}, { Bheem.body.x + Bheem.body.width+10.0f, Bheem.body.y + Bheem.body.height+10.0f }, { 1.0f, 0.0f, 0.0f , 0.0f }, { (float)j,0 }, 0);
					testrenderer.draw_quad({ Duryodhan.body.x , Duryodhan.body.y }, { Duryodhan.body.x + Duryodhan.body.width, Duryodhan.body.y + Duryodhan.body.height }, { 0.0f, 0.0f, 1.0f , 0.0f }, { 0,0 }, 1);
					//testrenderer.draw_quad({ Bheem.body.x-Bheem.body.radius - 5.0f, Bheem.body.y-Bheem.body.radius - 5.0f }, { Bheem.body.x+Bheem.body.radius + 5.0f, Bheem.body.y+ Bheem.body.radius + 5.0f }, { 1.0f, 0.0f, 0.0f , 0.0f }, {(float) j,0 },0);
					//testrenderer.draw_quad({ Duryodhan.body.x-Duryodhan.body.radius - 5.0f, Duryodhan.body.y- Duryodhan.body.radius - 5.0f }, { Duryodhan.body.x + Duryodhan.body.radius + 5.0f, Duryodhan.body.y + Duryodhan.body.radius + 5.0f }, { 0.0f, 0.0f, 1.0f , 0.0f }, { 0,0 }, 1);
					//testrenderer.draw_quad({ 30, 200 }, { 200.0f, 400.0f }, { 0.0f, 0.0f, 0.0f }, { (float)j,0 },1);
					//testrenderer.set_walls({ 0.0f,0.0f }, { 20.0f,720.0f }, { 1260.0f,0.0f }, { 1280.0f,720.0f });
					//testrenderer.set_walls({ 0.0f,0.0f }, { 1280.0f,20.0f }, { 0.0f,700.0f }, { 1280.0f,720.0f });
					//testrenderer.set_ground({ 0.0f,0.0f }, { 1280.0f,20.0f });
					float frameTime = ImGui::GetIO().DeltaTime;
					float fps = 1.0f / frameTime;

					
					ImGui::Begin("Engine Stats");
					ImGuiIO& io = ImGui::GetIO();
					ImGui::Text("FPS: %.1f", io.Framerate);
					ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
					ImGui::ColorEdit4("Background Color", screen_colors);
					ImGui::End();

					//cout << Duryodhan.health;
					testrenderer.End_Scene();
					
		        
	}
	

   return 0;
}

