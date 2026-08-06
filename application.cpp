#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <vlc/vlc.h>

#include "headers/window.h"
#include "headers/video.h"
#include "headers/VBO.h"
#include "headers/VAO.h"
#include "headers/camera.h"
#include "headers/common.h"
#include "headers/shader.h"
#include "headers/IBO.h"
#include "headers/texture.h"
#include "headers/renderer.h"
#include "headers/animation.h"

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
	video_player testplayer;
	if (testplayer.initialize())
	{
		cout << "VLC initialized successfully\n";
		cout << "Libvlc version :" << libvlc_get_version() << endl;
	}
	testplayer.load_media("resources/videos/video.mp4");
	if (!testplayer.play())
	{
		cout << "couldn't play";
		__debugbreak();
	}
	renderer2D testrenderer(1280, 720, "KURUKSHETRA TEST ENGINE");
	//cout << "\nsize is : " << sizeof(vertex);

	testrenderer.set_shader("resources/shaders/default.shader");
	testrenderer.set_texture("resources/textures/ideal_bheem.png");
	testrenderer.set_texture("resources/textures/dur.png");
	testrenderer.set_texture("resources/textures/kuruksetra backgrouknd v1.png");
	testrenderer.set_texture(testplayer.get_video_width(), testplayer.get_video_height());
	testrenderer.set_sampler_array("text");
	animation bheem_idle(testrenderer.get_texture_address(1), 1, 0.095f, { 372, 530 }, true, true);
	for (int i{ 0 }; i < 6; i++) bheem_idle.push({ 0 , i });
	animation love_you_gaming(testrenderer.get_texture_address(2), 9, 0.095f, { 92,91 }, false, false, true);
	//for (int i = 0; i < 8; i++)
	{
		/*for (int j = 0; j < 8; j++)
		{*/
		//if ((i == 2) && j >= 4 ) break;

	//	love_you_gaming.push({ 7,i });
	//}
	}

	/*testrenderer.add_texture("resources/textures/realtest.png");
	testrenderer.add_texture("resources/textures/kurukshetra.png");*/

	BoxCharacter Bheem(testrenderer.window_address(), 30.0f, 40.0f, 190.0f, 230.0f);
	BoxCharacter Duryodhan(testrenderer.window_address(), 800.0f, 40.0f, 230.0f, 250.0f);
	//Character Bheem(30.0f, 40.0f, 150.0f);
	//Character Duryodhan(640.0f, 360.0f, 150.0f);
	
	InputHandler testhandler;
	testhandler.setspeed(800.0f);
	testrenderer.vsync(1);
	
	//testrenderer.set_texture("resources/textures/slot0.png", 1 , 372, 530);
	float screen_colors[4] = { 0,1,0,1 };
	float frameTimer = 0.0f; // Har frame ka time jodega
	int j = 0;
	int direction = 1; // 1 matlab aage jaao, -1 matlab peeche
	float timer = 0.0f;
	float delay = 0.12f;  // Kitni der ek frame dikhega (in seconds)
	float x_mid, y_mid;
	testplayer.play();
	while (!testrenderer.is_window_closed())
	{
		if (Bheem.death()) testrenderer.update_camera({ Bheem.body.x,Bheem.body.y,0.0f });
		else if (Duryodhan.death()) testrenderer.update_camera({ Duryodhan.body.x,Duryodhan.body.y,0.0f });
		else
		{
			x_mid = ((Bheem.body.x + Duryodhan.body.x) / 2) - (1280 / 2);
			y_mid = (((Bheem.body.y + Duryodhan.body.y) / 2) - 100.0f);
			testrenderer.update_camera({ x_mid,y_mid,0.0f });
		}
		
		float deltaTime = ImGui::GetIO().DeltaTime; // Engine ka frame time


		Bheem.UpdatedPhysics(deltaTime);
		Duryodhan.UpdatedPhysics(deltaTime);
		bheem_idle.update(deltaTime);
		love_you_gaming.update(deltaTime);
		testhandler.ProcessInput(testrenderer.window_address(), Bheem, Duryodhan, testhandler, deltaTime);
		//testrenderer.processinput();
		
		testrenderer.set_colors(screen_colors[0], screen_colors[1], screen_colors[2], screen_colors[3]);

		cout << deltaTime << "\n";
		testrenderer.Begin_Scene(0);



		//if (deltaTime > 0.05f) deltaTime = 0.05f;
		testrenderer.update_texure(testplayer.get_video_buffer(), 4);
		testrenderer.set_backgroud(4);
		testrenderer.draw_quad({ Bheem.body.x, Bheem.body.y },
			{ Bheem.body.x + Bheem.body.width + 10.0f, Bheem.body.y + Bheem.body.height + 10.0f },
			{ 1.0f, 0.0f, 0.0f , 1.0f },
			bheem_idle.get_current_frame(),
			1.0f);

		//cout << "done drawing 1st quad\n";
		testrenderer.draw_quad({ Duryodhan.body.x , Duryodhan.body.y },
			{ Duryodhan.body.x + Duryodhan.body.width, Duryodhan.body.y + Duryodhan.body.height },
			{ 0.0f, 0.0f, 1.0f , 1.0f },
			love_you_gaming.get_current_frame(),
			2.0f);

		//Bheem.debug_draw();

		//testrenderer.set_walls({ 0,0 }, { 20,720 }, { 0.0f,0.0f,0.0f,0.0f }, {(float)j, 0}, 0);


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