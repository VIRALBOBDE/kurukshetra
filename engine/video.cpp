#include "video.h"

video_player::video_player()
{

}
bool video_player::wait_until_done()
{
    bool done = false;

    while (!done)
    {
        auto status = libvlc_media_get_parsed_status(m_media);

        if (status == libvlc_media_parsed_status_done)
        {
            done = true;
            break;
        }

        if (status == libvlc_media_parsed_status_failed ||
            status == libvlc_media_parsed_status_timeout ||
            status == libvlc_media_parsed_status_skipped)
        {
            done = false;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return done;
}

bool video_player::wait_until_done(video_data* video)
{
    bool done = false;

    while (!done)
    {
        auto status = libvlc_media_get_parsed_status(video->media);

        if (status == libvlc_media_parsed_status_done)
        {
            done = true;
            break;
        }

        if (status == libvlc_media_parsed_status_failed ||
            status == libvlc_media_parsed_status_timeout ||
            status == libvlc_media_parsed_status_skipped)
        {
            done = false;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return done;
}






bool video_player::parse_media()
{
    int status = libvlc_media_parse_with_options(
        m_media,
        libvlc_media_parse_local,
        -1);

    return status != -1;
}

bool video_player::parse_media(video_data* video)
{
    int status = libvlc_media_parse_with_options(
        video->media,
        libvlc_media_parse_local,
        -1);

    return status != -1;
}






bool video_player::extract_video_information()
{
    if (!parse_media())
        return false;

    return wait_until_done();
}

bool video_player::extract_video_information(video_data* video)
{
    if (!parse_media(video))
        return false;

    return wait_until_done(video);
}






bool video_player::read_video_metadata()
{
    libvlc_media_track_t** track_list = nullptr;

    unsigned track_count =
        libvlc_media_tracks_get(m_media, &track_list);

    bool found_video_track = false;

    if (track_count == 0)
        goto no_tracks_found;

    for (unsigned i = 0; i < track_count; i++)
    {
        if (track_list[i]->i_type == libvlc_track_video &&
            track_list[i]->video != nullptr)
        {
            if (track_list[i]->video->i_width != 0 &&
                track_list[i]->video->i_height != 0)
            {
                m_video_width = track_list[i]->video->i_width;
                m_video_height = track_list[i]->video->i_height;

                found_video_track = true;
                break;
            }
        }
    }

no_tracks_found:

    std::cout
        << "Width = " << m_video_width
        << " Height = " << m_video_height
        << std::endl;

    libvlc_media_tracks_release(track_list, track_count);

    return found_video_track;
}



bool video_player::read_video_metadata(video_data* video)
{
    libvlc_media_track_t** track_list = nullptr;

    unsigned track_count =
        libvlc_media_tracks_get(video->media, &track_list);

    bool found_video_track = false;

    if (track_count == 0)
        goto no_tracks_found;

    for (unsigned i = 0; i < track_count; i++)
    {
        if (track_list[i]->i_type == libvlc_track_video &&
            track_list[i]->video != nullptr)
        {
            if (track_list[i]->video->i_width != 0 &&
                track_list[i]->video->i_height != 0)
            {
                video->video_width = track_list[i]->video->i_width;
                video->video_height = track_list[i]->video->i_height;

                found_video_track = true;
                break;
            }
        }
    }


no_tracks_found:

    std::cout<< "video dimentions read :"
        << " Width = " << video->video_width
        << " Height = " << video->video_height
        << std::endl;

    libvlc_media_tracks_release(track_list, track_count);

    return found_video_track;
}

/* this was some tough shit
* and I guess there are levels to this shit
* sala eak function jisme functions pass hote hai and uppar se wo functions jo pass honge wo bhi ham hi batayenge
* crazy stuff bruh
*/
void* video_player::lock_callback(void* opaque, void** planes) 
{
    video_player* player = static_cast<video_player*>(opaque); 
    planes[0] = player->m_pixel_buffer; 
    return player; 
}

void* video_player::lockwa_callback(void* opaque, void** planes)
{
    video_data* player = static_cast<video_data*>(opaque);
    planes[0] = player->pixel_buffer;
   
    return player;
}

// this callback funtion is empty nothing to do here 
void video_player::unlock_callback(void* opaque, void* picture, void* const* planes)
{
}

void video_player::display_callback(void* opaque, void* picture)
{
   
}


video_player::~video_player()
{
    if (m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
    }

    if (m_media)
        libvlc_media_release(m_media);

    if (m_instance)
        libvlc_release(m_instance);

    if (m_pixel_buffer)
    {
        delete[] m_pixel_buffer;
        m_pixel_buffer = nullptr;
    }
    
}

bool video_player::initialize()
{
    m_instance = libvlc_new(0, NULL);

    if (!m_instance)
    {
        std::cerr << "Failed to create libvlc instance\n";
        return false;
    }

    return true;
}


void video_player::load_media(const std::string& media_path, bool loop)
{
    // agar media player already exist karta hai toh use destroy kar do
    if (m_media_player)
    {
        libvlc_media_player_stop(m_media_player);
        libvlc_media_player_release(m_media_player);
        m_media_player = nullptr;
    }

    // agar media ki details already exist karti hai toh unhe bhi destroy kar do
    if (m_media)
    {
        libvlc_media_release(m_media);
        m_media = nullptr;
    }

    // media ki details naye se banao and store karo
    std::cout << m_media;
    m_media = libvlc_media_new_path(m_instance, media_path.c_str());
    if (!m_media)
    {
        std::cerr << "Failed to create media\n";
        __debugbreak();
    }

    if ( loop ) libvlc_media_add_option( m_media, ":input-repeat=100" );

    // extracting video information
    if (!extract_video_information())   
    {
        std::cerr << "Failed in extraction of video information. Please check!\n";
        __debugbreak();
    }

    // reading video metadata
    if (!read_video_metadata())
    {
        std::cerr << "Failed in reading video metadata. Please check!\n";
        __debugbreak();
    }

    // agar pehle se buffer allocated hai toh use free kar do
    if (m_pixel_buffer)
    {
        delete[] m_pixel_buffer;
        m_pixel_buffer = nullptr;
        m_buffer_size = 0;
    }

    // naya pixel buffer allocate karo
    m_buffer_size = m_video_width * m_video_height * 4;
    m_pixel_buffer = new unsigned char[m_buffer_size];

    // media player create karo
    m_media_player = libvlc_media_player_new_from_media(m_media);
    if (!m_media_player)
    {
        std::cerr << "Failed to create player\n";
        m_media_player = nullptr;
        __debugbreak();
    }

    std::cout << "buffer = "
        << static_cast<void*>(m_pixel_buffer)
        << '\n';

    // callbacks register karo
    libvlc_video_set_callbacks(
        m_media_player,
        lock_callback,
        unlock_callback,
        display_callback,
        this
    );

    std::cout << "buffer = "
        << static_cast<void*>(m_pixel_buffer)
        << '\n';

    std::cout << "buffer = "
        << static_cast<void*>(m_pixel_buffer)
        << '\n';

    // VLC ko batao ki ham kis format ka buffer provide kar rahe hain
    libvlc_video_set_format(
        m_media_player,
        "RV32",
        m_video_width,
        m_video_height,
        m_video_width * 4
    );
}

void video_player::load_media(const std::string& media_path, const std::string& media_name, bool loop)
{
    videos.emplace(media_name, new video_data);
    videos[media_name]->path = media_path;
    video_data* data = videos[media_name];



    data->media = libvlc_media_new_path(m_instance, media_path.c_str());
    if (!data->media)
    {
        std::cerr << "Failed to create media\n";
        __debugbreak();
    }


    if (loop) libvlc_media_add_option(data->media, ":input-repeat=100");

    if (!extract_video_information(data))
    {
        std::cerr << "Failed in extraction of video information. Please check!\n";
        __debugbreak();
    }

    if (!read_video_metadata(data))
    {
        std::cerr << "Failed in reading video metadata. Please check!\n";
        __debugbreak();
    }

    data->media_player = libvlc_media_player_new_from_media(data->media);
    if (!data->media_player)
    {
        std::cerr << "Failed to create player\n";
        data->media_player = nullptr;
        __debugbreak();
    }

    data->buffer_size = data->video_width * data->video_height * 4;
    data->pixel_buffer = new unsigned char[data->buffer_size];

    libvlc_video_set_callbacks(
        data->media_player,
        lockwa_callback,
        unlock_callback,
        display_callback,
        data
    );
    libvlc_video_set_format(
        data->media_player,
        "RV32",
        data->video_width,
        data->video_height,
        data->video_width * 4
    );
    
}


bool video_player::play()
{
    int result =
        libvlc_media_player_play(m_media_player);

    return result != -1;
}

bool video_player::play(const std::string& media_name)
{
    //if (m_pixel_buffer)
    //{
    //    delete[] m_pixel_buffer;
    //    m_pixel_buffer = nullptr;
    //    m_buffer_size = 0;
    //}


    //video_data* video = videos[media_name];
    //m_pixel_buffer = video->pixel_buffer;
    //m_buffer_size = video->video_width * video->video_height * 4;
    //m_pixel_buffer = new unsigned char[m_buffer_size];
    int result =
        libvlc_media_player_play(videos[media_name]->media_player);

    return result != -1;
}
