#include "drawing system.h"

drawing_system::drawing_system(renderer2D& renderer_address)
	:
	renderer ( renderer_address )
{
}

void drawing_system::turn_on_vsync()
{
	renderer.vsync(1);
}

void drawing_system::turn_of_vsync()
{
	renderer.vsync(0);
}

void drawing_system::set_bg_colors(glm::vec4 color_rgba_values)
{
	renderer.set_colors(color_rgba_values.x, color_rgba_values.y, color_rgba_values.z, color_rgba_values.w);
}

renderer2D* drawing_system::get_renderer_address()
{
	return &renderer;
}

void drawing_system::begin_scene()
{
	renderer.Begin_Scene();
}

void drawing_system::end_scene()
{
	renderer.End_Scene();
}

GLFWwindow* drawing_system::get_window_address()
{
	return renderer.window_address();
}

bool drawing_system::check_window_status()
{

	return renderer.is_window_closed();
}

void drawing_system::draw(drawing_data& input_data_to_draw)
{
	renderer.draw_quad
	(
		input_data_to_draw.left_bottom_corner,
		input_data_to_draw.right_top_corner,
		input_data_to_draw.rgba_value,
		input_data_to_draw.texturecoordinates,
		input_data_to_draw.texture_index
	);
}

void drawing_system::draw_quad(glm::vec2 lower_bootom_corner, glm::vec2 upper_top_corner, glm::vec4 r_g_b_values, glm::vec4 texture_coordinates, float texture_index)
{
	renderer.draw_quad
	(
		lower_bootom_corner,
		upper_top_corner,
		r_g_b_values,
		texture_coordinates,
		texture_index
	);
}

void drawing_system::destroy()
{
}

drawing_system::~drawing_system()
{
}

void drawing_system::set_texture(std::string address_of_the_texture)
{
	renderer.set_texture(address_of_the_texture);
}

void drawing_system::set_texture(int width, int height)
{
	renderer.set_texture(width, height , 4);
}

texture* drawing_system::get_texture_address(int index)
{
	return renderer.get_texture_address(index);
}

void drawing_system::update_texture(const unsigned char* frame_buffer, int index)
{
	renderer.update_texture(frame_buffer, index);
}

void drawing_system::set_background(int index_of_the_image_or_video)
{
	renderer.set_backgroud(index_of_the_image_or_video);
}

void drawing_system::set_shader(std::string address_of_the_shader)
{
	renderer.set_shader(address_of_the_shader);
}

void drawing_system::set_shader_uniform(std::string name_of_the_sampler)
{
	renderer.set_sampler_array(name_of_the_sampler);
}

void drawing_system::update_camera(glm::vec3 positions)
{
	renderer.update_camera(positions);
}
