#pragma once

#include <vlc/vlc.h>
#include <iostream>

class video_player
{

private:
	libvlc_instance_t* m_instance;
	libvlc_media_t* m_media;
	libvlc_media_player_t* m_media_player;

public:

	//  Constructor
	video_player()
	{
		m_instance		= NULL;
		m_media			= NULL;
		m_media_player	= NULL;
	}

	//  Destructor
	~video_player()
	{
		if(m_media_player)
		{
			libvlc_media_player_stop(m_media_player);
			libvlc_media_player_release(m_media_player);
		}
		if (m_media)
		{
			libvlc_media_release(m_media);
		}
		if (m_instance)
		{
			libvlc_release(m_instance);
		}
	}

	//  Other important functions
	bool initialize()
	{
		m_instance = libvlc_new(0, NULL);
		if (!m_instance)
		{
			std::cerr << "Failed to create libvlc instance" << std::endl;
			__debugbreak();
			//return false;
		}
		return true;
	}

	void load_media(const std::string& media_path)
	{
		if (m_media_player)
		{
			libvlc_media_player_stop(m_media_player);
			libvlc_media_player_release(m_media_player);
			m_media_player = NULL;
		}
		 
		if (m_media)
		{
			libvlc_media_release(m_media);
			m_media = NULL;
		}
		m_media = libvlc_media_new_path(m_instance, media_path.c_str());
		if (!m_media)
		{
			std::cerr << "Failed to create media\n";

			__debugbreak();
		}

		m_media_player = libvlc_media_player_new_from_media( m_media );
		if (!m_media_player)
		{
			std::cerr << "Failed to create player\n";
			m_media_player = nullptr;
			__debugbreak();
		}
	}

	void play()
	{

	}



};