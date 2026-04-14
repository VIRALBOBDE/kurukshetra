#pragma once
#include "camera.h"
#include "../to be tested/character.h"
#include "../to be tested/box.h"
#include "common.h"
#include "error.h"
#include "IBO.h"
#include "shader.h"
#include "subtexture.h"
#include "texture.h"
#include "VAO.h"
#include "VBO.h"
#include "window.h"
#include <iostream>
#include <array>
#include <string>
#include <vector>
using namespace std;
class renderer2D
{
private:
	//hamare engine ki limit
	static const size_t       MaxQuadCount    = 1000            ;  // 1000 Squares draw kar paayega
	static const size_t       MaxVertexCount  = MaxQuadCount * 4;  // 4000 Vertices honge 1000 squares ke
	static const size_t       MaxIndexCount   = MaxQuadCount * 6;  // 6000 Indices honge 1000 squares ke
	static const size_t       MaxTextureSlots = 32              ;  // maximum amount of textureslots
	glm::mat4                 viewprojectionmatrix;

	//saare important things ke heap mai objects bana ke unke addresses store kar lenge
	camera*                    m_camera                                 ;
	subtexture*                 m_subtexture                             ;
	ibo*                       m_ibo                                    ;
	shader*                    m_shader                                 ;
	texture*                   m_texture                                ;
	vao*                       m_vao	                                ;
	vbo*                       m_vbo	                                ;
	window*                    m_window                                 ;
	vertex*                    m_buffer_base   = new vertex[4000]		;
	vertex*                    m_buffer_ptr    = m_buffer_base			;
	unsigned int*              m_ibo_buffer    = new unsigned int[6000] ;
	unsigned int               white_texture                            ;
	int                        m_texture_slot[32]                       ;
	vector<Box>                m_wall_vector                            ;
	int          texture_counter = 0 ;
	int m_width, m_height;
	bool bheem_values = false, duryodhan_values = false;

	//    TESTING RANDOM THINGS

	//===================  TESTING THIS ============================//
	unsigned int raw_vbo_id;
	//===================  TESTING THIS ============================//

	//    PRIVATE FUNCTIONS
	void start_batch();
	void set_wall_coordinates(glm::vec2 coordinates);
public:
	renderer2D(int width, int height , const char* name);
	void set_shader(string name_of_the_shader);
	void set_shader(string name_of_the_shader , int fragment_shader_sampler_count);
	void set_texture(string name_of_the_texture , int slot , int tile_width , int tile_height);
	void set_texture(string name_of_the_texture, int slot);
	void set_camera();
	bool is_window_closed() const { return m_window->iswindowclose(); }
	GLFWwindow* window_address() const { return m_window->windowadd(); }
	void Begin_Scene(int texture_slot);
	void set_colors(float r, float g, float b, float a) { m_window->setcolors(r, g, b, a); }
	void End_Scene();
	void draw_quad(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec4 r_g_b_values , glm::vec2 texture_indices , int texture_no);// vertex* structure_batao);
	void Flush();
	~renderer2D();
	//void setuniform(string name_of_uniform  ,  float* data);
	//void swap_buffers();

	//temporary functions
	void draw_quad(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec3 r_g_b_values, vertex *structure_batao);
	void bindvao() { m_vao->bind(); };
	void bind_texture(int slot) { m_texture->bind(slot); }
	void bind_shader() { m_shader->use(); }
	void fill_vbo_data(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec3 r_g_b_values, glm::vec2 texture_indices, int texture_no);
	void new_frame();
	/*void set_walls(glm::vec2 left_wall_lower_bottom , glm::vec2 left_wall_upper_top , glm::vec2 right_wall_lower_bottom , glm::vec2 right_wall_upper_top );
	void set_ground(glm::vec2 ground_botttom_left_corner, glm::vec2 ground_top_right_corner);
	void processinput();*/
};