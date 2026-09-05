#include "renderer.h"
#include "../game/common data/drawing data.h"
#include <iostream>
class drawing_system
{
private:
	renderer2D& renderer;
public :
	//constructor
	drawing_system(renderer2D& renderer_address);

	//renderer related functions
	renderer2D* get_renderer_address();
	void turn_on_vsync();
	void turn_of_vsync();
	void set_bg_colors(glm::vec4 color_rgb_values);
	void begin_scene();
	void end_scene();

	//window related functions
	GLFWwindow* get_window_address();
	bool check_window_status();


	//texture related functions 
	void set_texture(std::string address_of_the_texture);
	void set_texture(int width, int height);
	void update_texture(const unsigned char* frame_buffer, int index);
	void set_background(int index_of_the_image_or_video);
	texture* get_texture_address(int index);

	//shader related functions
	void set_shader	(std::string address_of_the_shader);
	void set_shader_uniform(std::string name_of_the_sampler);

	//camera related functions 
	void update_camera(glm::vec3 positions);

	//drawing related functions 
	void draw		(drawing_data& input_data_to_draw);
	void draw_quad
	(
		glm::vec2 lower_bootom_corner,
		glm::vec2 upper_top_corner,
		glm::vec4 r_g_b_values,
		glm::vec4 texture_coordinates,
		float texture_index
	);




	//desturctor
	void destroy();
	~drawing_system();
};