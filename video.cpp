#include "headers/video.h"

bool video_player::wait_until_done()
{
	bool done = false;
	while (!done)
	{
		auto status = libvlc_media_get_parsed_status(m_media);
		if ((status == libvlc_media_parsed_status_skipped) || (status == libvlc_media_parsed_status_failed) || (status == libvlc_media_parsed_status_timeout))
		{
			done = false;
			break;
		}
		else if ((status == libvlc_media_parsed_status_done))
		{
			done = true;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return done;
}

bool video_player::parse_media()
{
	int status = libvlc_media_parse_with_options(m_media, libvlc_media_parse_local, -1);
	return (status == -1) ? false : true;
}

bool video_player::extract_video_information()
{
	if (!parse_media())
		return false;
	
	return wait_until_done();
}

bool video_player::read_video_meta_data()
{
	libvlc_media_track_t** track_list = nullptr;
	unsigned track_count = libvlc_media_tracks_get(m_media, &track_list);
	if (track_count == 0) return false;
	for (int i{ 0 }; i < track_count; i++)
	{
		if (track_list[i]->i_type == libvlc_track_video)
		{

		}
	}
}

video_player::video_player()
{
	m_instance = NULL;
	m_media = NULL;
	m_media_player = NULL;
}

video_player::~video_player()
{
	if (m_media_player)
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

bool video_player::initialize()
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

void video_player::load_media(const std::string& media_path)
{
	// agar media player already exist karta hai toh use destroy kar do 
	if (m_media_player)
	{
		libvlc_media_player_stop(m_media_player);
		libvlc_media_player_release(m_media_player);
		m_media_player = NULL;
	}

	// agar media ki details already exist karti hai toh unhe bhi destroy kar do 
	if (m_media)
	{
		libvlc_media_release(m_media);
		m_media = NULL;
	}

	// media ki details naye se banao and store karo
	m_media = libvlc_media_new_path(m_instance, media_path.c_str());
	if (!m_media)
	{
		std::cerr << "Failed to create media\n";

		__debugbreak();
	}

	// media player ki details naye se banao and store karo
	m_media_player = libvlc_media_player_new_from_media(m_media);
	if (!m_media_player)
	{
		std::cerr << "Failed to create player\n";
		m_media_player = nullptr;
		__debugbreak();
	}
}

bool video_player::play()
{
	int result = libvlc_media_player_play(m_media_player);
	if (result == -1)
	{
		std::cerr << "media_player is null ,  cant play\n";
		return false;
	}
	return true;
}
