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


#include "../engine/video.h"
#include "../engine/renderer.h"
#include "../engine/animation.h"
#include "../engine/drawing system.h"

//the following header files are not completed yet 
#include "game's dustbin/box.h"
#include "game's dustbin/circular character.h"
#include "game's dustbin/Circle.h"
#include "game's dustbin/Character.h"
#include "game's dustbin/moves.h"
#include "input handling/InputHandling.h"
#include "physics.h"


int main()
{
	video_player* testplayer = new video_player;
	if (testplayer->initialize())
	{
		cout << "VLC initialized successfully\n";
		cout << "Libvlc version :" << libvlc_get_version() << endl;
	}
	testplayer->load_media("resources/videos/video.mp4");
	if (!testplayer->play())
	{
		cout << "couldn't play";
		__debugbreak();
	}

	renderer2D* testrenderer = new renderer2D(1280, 720, "KURUKSHETRA TEST ENGINE");
	{
		drawing_system test_drawer(*testrenderer);
		//cout << "\nsize is : " << sizeof(vertex);

		test_drawer.set_shader("resources/shaders/default.shader");
		test_drawer.set_texture("resources/textures/cute ghost.png");
		test_drawer.set_texture("resources/textures/dur.png");
		test_drawer.set_texture("resources/textures/kuruksetra backgrouknd v1.png");
		test_drawer.set_texture(testplayer->get_video_width(), testplayer->get_video_height());
		test_drawer.set_shader_uniform("text");
		animation bheem_idle;
		bheem_idle.set_vals(test_drawer.get_texture_address(1), 9, 1.0f, { 92,92 }, true, true);
		for (int i{ 0 }; i < 2; i++) bheem_idle.push({ 0 , i });
		animation love_you_gaming(test_drawer.get_texture_address(2), 9, 0.095f, { 92,91 }, false, false, true);
		//for (int i = 0; i < 8; i++)

			/*for (int j = 0; j < 8; j++)
			{*/
			//if ((i == 2) && j >= 4 ) break;

		//	love_you_gaming.push({ 7,i });
		//}


		/*testrenderer->add_texture("resources/textures/realtest.png");
		testrenderer->add_texture("resources/textures/kurukshetra.png");*/

		BoxCharacter Bheem(test_drawer.get_window_address(), 30.0f, 40.0f, 190.0f, 230.0f);
		//Bheem.set_animations(0, 2, 9, { 92, 92 }, 0.095f, true, true);
		BoxCharacter  Ghost(1, test_drawer.get_renderer_address(), { 40,40,92,92 }, { 40,40,90,90 });
		Ghost.set_animations(0, 0, 2, 9, 1.0f, { 92,92 }, true, false, false);

		BoxCharacter Duryodhan(test_drawer.get_window_address(), 800.0f, 40.0f, 230.0f, 250.0f);
		//Character Bheem(30.0f, 40.0f, 150.0f);
		//Character Duryodhan(640.0f, 360.0f, 150.0f);

		InputHandler testhandler;

		testhandler.setspeed(800.0f);
		test_drawer.turn_of_vsync();

		//testrenderer->set_texture("resources/textures/slot0.png", 1 , 372, 530);
		float screen_colors[4] = { 0,1,0,1 };
		float frameTimer = 0.0f; // Har frame ka time jodega
		int j = 0;
		int direction = 1; // 1 matlab aage jaao, -1 matlab peeche
		float timer = 0.0f;
		float delay = 0.12f;  // Kitni der ek frame dikhega (in seconds)
		float x_mid, y_mid;
		testplayer->play();
		while (!test_drawer.check_window_status())
		{
			if (Bheem.death()) test_drawer.update_camera({ Bheem.body.x,Bheem.body.y,0.0f });
			else if (Duryodhan.death()) test_drawer.update_camera({ Duryodhan.body.x,Duryodhan.body.y,0.0f });
			else
			{
				x_mid = ((Bheem.body.x + Duryodhan.body.x) / 2) - (1280 / 2);
				y_mid = (((Bheem.body.y + Duryodhan.body.y) / 2) - 100.0f);
				test_drawer.update_camera({ x_mid,y_mid,0.0f });
			}

			float deltaTime = ImGui::GetIO().DeltaTime; // Engine ka frame time


			Bheem.Update(deltaTime, Duryodhan);
			Duryodhan.Update(deltaTime, Bheem);
			bheem_idle.update(deltaTime);
			love_you_gaming.update(deltaTime);
			testhandler.ProcessInput(test_drawer.get_window_address(), Bheem, Duryodhan, testhandler, deltaTime);
			//testrenderer->processinput();

			test_drawer.set_bg_colors({ screen_colors[0], screen_colors[1], screen_colors[2], screen_colors[3] });

			cout << deltaTime << "\n";
			test_drawer.begin_scene();

			//system.draw( Bheem.drawing_data ) ;

			//if (deltaTime > 0.05f) deltaTime = 0.05f;
			test_drawer.update_texture(testplayer->get_video_buffer(), 4);
			test_drawer.set_background(4);
			test_drawer.draw_quad({ Bheem.body.x, Bheem.body.y },
				{ Bheem.body.x + Bheem.body.width + 10.0f, Bheem.body.y + Bheem.body.height + 10.0f },
				{ 1.0f, 0.0f, 0.0f , 1.0f },
				bheem_idle.get_current_frame(),
				1.0f);

			//Bheem.draw({ 0,0,1,1 } , deltaTime , bheem_idle.get_current_frame());

			//cout << "done drawing 1st quad\n";
			test_drawer.draw_quad({ Duryodhan.body.x , Duryodhan.body.y },
				{ Duryodhan.body.x + Duryodhan.body.width, Duryodhan.body.y + Duryodhan.body.height },
				{ 0.0f, 0.0f, 1.0f , 1.0f },
				love_you_gaming.get_current_frame(),
				2.0f);

			//Bheem.debug_draw();


			float frameTime = ImGui::GetIO().DeltaTime;
			float fps = 1.0f / frameTime;


			ImGui::Begin("Engine Stats");
			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("FPS: %.1f", io.Framerate);
			ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
			ImGui::ColorEdit4("Background Color", screen_colors);
			ImGui::End();

			test_drawer.end_scene();


		}
	}
	free(testrenderer);
	free(testplayer);

	return 0;
}