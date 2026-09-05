#include "headers/video.h"

/* this was some tough shit
* and I guess there are levels to this shit 
* sala eak function jisme functions pass hote hai and uppar se wo functions jo pass honge wo bhi ham hi batayenge
* crazy stuff bruh
 */
void* video_player::lock_callback(void* opaque, void** planes)
{
	video_player* player = static_cast<video_player*>(opaque);
	planes[0] = player->m_pixel_buffer;
	std::cout << "lock_callback\n";
	return player;
}

// this callback funtion is empty nothing to do here
void video_player::unlock_callback(void* opaque, void* picture, void* const* planes)
{
	std::cout << "unlock_callback\n";
}

// this callback is also empty , nothing intrusting here
void video_player::display_callback(void* opaque, void* picture)
{
	std::cout << "display_callback\n";
}





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

bool video_player::read_video_metadata()
{
	libvlc_media_track_t** track_list = nullptr;
	unsigned track_count = libvlc_media_tracks_get(m_media, &track_list);
	bool found_video_track = false;
	if (track_count == 0)
	{
		libvlc_media_tracks_release(track_list, track_count);
		return found_video_track;
	}
	for (unsigned i{ 0 }; i < track_count; i++)
	{
		if (track_list[i]->i_type == libvlc_track_video && track_list[i]->video != nullptr)
		{
			auto* video = track_list[i]->video;
			if (video->i_height != 0 && video->i_width != 0)
			{
				m_video_height = video->i_height;
				m_video_width  = video->i_width;
				found_video_track = true;
				break;
			}
		}
	}
	libvlc_media_tracks_release(track_list, track_count);
	return found_video_track;
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

	// extracting video information
	if ( !extract_video_information() )
	{
		std::cerr << "failed in extraction of video information . PLS CHECK!\n";
		__debugbreak();
	}

	//reading video matadata
	if (!read_video_metadata())
	{
		std::cerr << "failed in reading video matadata . PLS CHECK!\n";
		__debugbreak();
	}

	if (m_pixel_buffer)
	{
		delete[] m_pixel_buffer  ;
		m_pixel_buffer = nullptr ;
		m_buffer_size  = 0		 ;
	}
	m_buffer_size = m_video_width * m_video_height * 4;
	m_pixel_buffer = new unsigned char[m_buffer_size];

	// media player ki details naye se banao and store karo
	m_media_player = libvlc_media_player_new_from_media(m_media);
	if (!m_media_player)
	{
		std::cerr << "Failed to create player\n";
		m_media_player = nullptr;
		__debugbreak();
	}


	// callbacks ko regiester kar rahe hai iss line mai ham . abhi ke liye dekh ke confuse ni hona thora sa advanced concept hai
	libvlc_video_set_callbacks( m_media_player , lock_callback , unlock_callback , display_callback, this ) ;

	// buffer mai data ko kaise register karna hai wo bata rahe hai iss line mai .
	libvlc_video_set_format(m_media_player, "RV32", m_video_width, m_video_height, (m_video_width * 4));
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

int video_player::get_video_height()
{
	return m_video_height;
}

int video_player::get_video_width()
{
	return m_video_width;
}

const unsigned char* video_player::get_video_buffer()
{
	return m_pixel_buffer;
}
