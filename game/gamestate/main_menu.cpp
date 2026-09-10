#include "main_menu.h"


void main_menu::init(state_manager* manager)
{
	// set up the video player
	manager->video->load_media("resources/videos/main-menu-bg.mp4","main_menu_bg", true);
    manager->video->load_media("resources/videos/Duryodhan Idle .mov", "duryodhan", true);

	//load resources
	manager->renderer->set_texture("resources/textures/play.png");
	manager->renderer->set_texture("resources/textures/quit.png");
	manager->renderer->set_texture(manager->video->get_video_width("main_menu_bg"), manager->video->get_video_height("main_menu_bg"));
    manager->renderer->set_texture(manager->video->get_video_width("duryodhan"), manager->video->get_video_height("duryodhan"));
	manager->renderer->set_shader_uniform("text");
    manager->renderer->set_uniform_matrix("model", glm::mat4(1.0f));

	//set data
	play.set_data({ 960,400 }, { 1160,550 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.0f,0.0f,1.0f,1.0f }, 1);
	quit.set_data({ 900,200 }, { 1160,350 }, { 0.0f,0.0f,1.0f,0.4f }, { 0.0f,0.0f,1.0f,1.0f }, 2);
    duryodhan.set_data({ 440,160 }, { 840 , 560 }, { 1.0f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,0.0f,0.0f }, 4);
	
}

void main_menu::pre_loop_function(state_manager* manager)
{
	manager->video->play("main_menu_bg");
    manager->video->play("duryodhan");
}

void main_menu::update(state_manager* manager, float del_time)
{
	manager->renderer->update_texture(manager->video->get_video_buffer("main_menu_bg"), 3);
    manager->renderer->update_texture(manager->video->get_video_buffer("duryodhan"), 4);
}

void main_menu::draw(drawing_system* renderer)
{
    
	renderer->begin_scene();
	renderer->set_background(3);
    renderer->draw(duryodhan);
	renderer->draw(play);
	renderer->draw(quit);
	renderer->end_scene();
    
}


// SANKEY VAI ZINDABAAD

void main_menu::poll_events(GLFWwindow* window, state_manager * manager)
{
    //down - quit
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (down_released)
            {
                currently_chosen = 2;

                play.rgba_value.w = 0.4f;
                quit.rgba_value.w = 1.0f;

                down_released = false;
            }
        }
        else
        {
            down_released = true;
        }

        // up - play
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (up_released)
            {
                currently_chosen = 1;

                play.rgba_value.w = 1.0f;
                quit.rgba_value.w = 0.4f;

                up_released = false;
            }
        }
        else
        {
            up_released = true;
        }

        //enter - selected action
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            if (currently_chosen == 1)
            {
                manager->change_state(new fight_scene);
            }
            else if (currently_chosen == 2)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }
    
}