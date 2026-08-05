#pragma once
#include "animation.h"
#include "camera.h"
//#include "../to be tested/character.h"
#include "../to be tested/Character.h"
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
	glm::mat4                 viewprojectionmatrix				;

	//saare important things ke heap mai objects bana ke unke addresses store kar lenge
	camera*                    m_camera        =   nullptr							;
	ibo*                       m_ibo           =   nullptr							;
	shader*                    m_shader        =   nullptr							;
	vao*                       m_vao	       =   nullptr							;
	vbo*                       m_vbo	       =   nullptr							;
	window*                    m_window        =   nullptr							;
	vertex*                    m_buffer_base   =   new vertex[4000]					;
	vertex*                    m_buffer_ptr    =   m_buffer_base					;
	unsigned int*              m_ibo_buffer    =   new unsigned int[6000]			;
	int						   texture_counter =   1								;
	//subtexture*				   m_subtexture	  [32]								;
	texture*                   m_texture	  [32]									;
	int						   m_texture_slot [32]									;
	glm::vec4                  m_boxes[MaxVertexCount]								;

	unsigned int               white_texture										;
	vector<Box>                m_wall_vector										;
	int						   m_width, m_height									;
	bool					   bheem_values = false , duryodhan_values = false		;
	

	enum debug_boxes
	{
		hurt = 0 , hit = 1 , wall = 2
	};

	//    TESTING RANDOM THINGS

	//===================  TESTING THIS ============================//
	unsigned int raw_vbo_id;
	//===================  TESTING THIS ============================//

	//    PRIVATE FUNCTIONS
	void start_batch();
	void set_wall_coordinates(glm::vec2 coordinates);
public:

	renderer2D(int width, int height , const char* name);

	//setters
	void set_shader			(string name_of_the_shader);
	void set_shader			(string name_of_the_shader , int fragment_shader_sampler_count);
	void set_texture		(string name_of_the_texture );
	void set_walls			(glm::vec2 left_bottom_corner, glm::vec2 width_and_height, glm::vec4 r_g_b_values , glm::vec2 texture_indices , float texture_no);
	void set_colors			(float r, float g, float b, float a) { m_window->setcolors(r, g, b, a); }
	void set_sampler_array	(std::string name_of_sampler);
	inline void set_sampler		(string name_of_uniform, int sampler_count , int* sampler_array);
	void set_backgroud		(float texture_slot);
	//getters
	texture* get_texture_address(int slot) { return m_texture[slot]; }

	void update_camera(glm:: vec3 position);
	void Begin_Scene	(int texture_slot);
	void draw_quad		(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec4 r_g_b_values , glm::vec2 texture_indices , int texture_no);// vertex* structure_batao);
	void draw_quad		(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec4 r_g_b_values, glm::vec4 texture_coordinates  , int texture_no );
	void draw_quad		(BoxCharacter character_details , debug_boxes type_of_box);
	void set_camera();
	void End_Scene();
	void Flush();
	void vsync(int true_or_false)           {  glfwSwapInterval(true_or_false); }
	bool		is_window_closed()		const	{ return m_window->iswindowclose(); }
	GLFWwindow* window_address()		const	{ return m_window->windowadd();		}
	~renderer2D();

	//temporary functions
	void draw_quad(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec3 r_g_b_values, vertex *structure_batao);
	void bindvao() { m_vao->bind(); };
	void bind_texture(int slot) { m_texture[slot]->bind(); }
	void bind_shader() { m_shader->use(); }
	void fill_vbo_data(glm::vec2 left_bottom_corner, glm::vec2 right_top_corner, glm::vec4 r_g_b_values, glm::vec4 texture_indices, int texture_no);
	void new_frame();
};
	/*void set_walls(glm::vec2 left_wall_lower_bottom , glm::vec2 left_wall_upper_top , glm::vec2 right_wall_lower_bottom , glm::vec2 right_wall_upper_top );
	void set_ground(glm::vec2 ground_botttom_left_corner, glm::vec2 ground_top_right_corner);
	void processinput();*/
	//void setuniform(string name_of_uniform  ,  float* data);
	//void swap_buffers();
	//void add_texture(string name_of_the_texture);