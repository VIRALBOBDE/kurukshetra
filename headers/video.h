#pragma once

#include <thread>
#include <chrono>
#include <vlc/vlc.h>
#include <iostream>

class video_player
{

private:
	unsigned char* buffer          = nullptr		;
	libvlc_instance_t* m_instance  = nullptr		;
	libvlc_media_t* m_media        = nullptr		;
	libvlc_media_player_t* m_media_player = nullptr	;
	unsigned char* m_pixel_buffer  = nullptr		;
	int m_video_width				{ 0 }	;
	int m_video_height				{ 0 }	;

	bool wait_until_done();
	bool parse_media();
	bool extract_video_information( ) ;
	bool read_video_meta_data();
public:

	//  Constructor
	video_player();

	//  Destructor
	~video_player();

	//  Other important functions
	bool initialize();

	void load_media(const std::string& media_path);

	bool play();



};