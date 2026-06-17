#pragma once

//inbuilt libraries
#include <iostream>
#include <string.h>
#include <vector>

//external libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//custom libraries
#include "subtexture.h"
#include "texture.h"

//struct texture_coordinates
//{
//	glm::vec2 left_bottom_corner, top_right_corner	;
//};

class animation
{
private:
	bool			is_looping{ true }, ping_pong_animation{ false }, backward_direction{ true }, full_image{ false };
	int             current_frame  { 0 }																;
	float			frame_duration{ 0.0f }  , time_lapsed{ 0.0f }										;
	float			delta_time			                                                                ;
	texture*		l_texture																			;
	subtexture      subtexture2d																		;
	glm::vec2		tile_size																			;
	glm::vec2       texture_size																		;
	glm::vec4       section_size	{ 0.0f,0.0f,0.0f,0.0f }												;
	std::vector     <subtexture> frames																	;

protected:
	glm::vec4 get_section_size() { return section_size; }
	//static void update_delta_time(float time) { delta_time = time ; }
public:

	animation() {}
	/*
	yaha pe maine apne variables ka naam change kiya hai 
	frames		-> frame 
	frame_delay -> frame_duration
	is_walking  -> is_looping
	*/
	animation(	texture* texture_object , 
				float frame_delay ,
				glm::vec2 tile_dimentions  ,
				bool is_walking = true ,
				bool ping_pong_motion = false,
				bool full_texture = false
			 )
		:
		frame_duration	(frame_delay),
		is_looping		(is_walking) ,
		l_texture		(texture_object) ,
		tile_size        (tile_dimentions),
		ping_pong_animation (ping_pong_motion),
		full_image		(full_texture)
		{
		texture_size.x = l_texture->getwidth();
		cout << "animation class sheet size :" << texture_size.x ;
		texture_size.y = l_texture->getheight();
		cout << " X " << texture_size.y << "\n";
		if(full_texture == true)	set_coordinates({ tile_size });
		}

	//ye function har eak frame mai delta_time ko change karta hai
	void update(float delta_timee);

	inline void set_coordinates(glm::vec2 coordinates) { push({ 0,0 }); frames[0].set_coordinates({ 0,0,1,1 }); }

	void push(glm::vec2 indices) ;

	inline void change_frame_delay(float frame_duration) { this->frame_duration = frame_duration ;  }

	glm::vec4 const get_current_frame( ) ; 

};