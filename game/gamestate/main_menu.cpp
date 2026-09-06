#include "main_menu.h"


void main_menu::init(state_manager* manager)
{
	// set up the video player
	manager->video->load_media("resources/videos/infinitycastle.mp4");

	//load resources
	manager->renderer->set_texture("resources/textures/play.png");
	manager->renderer->set_texture("resources/textures/quit.png");
	manager->renderer->set_texture(manager->video->get_video_width(), manager->video->get_video_height());
	manager->renderer->set_shader_uniform("text");

	//set data
	play.set_data({ 50,400 }, { 250,550 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.0f,0.0f,1.0f,1.0f }, 1);
	quit.set_data({ 50,200 }, { 250,350 }, { 0.0f,0.0f,1.0f,1.0f }, { 0.0f,0.0f,1.0f,1.0f }, 2);
	
}

void main_menu::pre_loop_function(state_manager* manager)
{
	manager->video->play();
}

void main_menu::update(state_manager* manager, float del_time)
{
	manager->renderer->update_texture(manager->video->get_video_buffer(), 3);
}

void main_menu::draw(drawing_system* renderer)
{
	renderer->begin_scene();
	renderer->set_background(3);
	renderer->draw(play);
	renderer->draw(quit);
	renderer->end_scene();
}

void main_menu::poll_events(GLFWwindow* window)
{

}