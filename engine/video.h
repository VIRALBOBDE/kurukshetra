#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vlc/vlc.h>

struct video_data
{
    libvlc_media_t* media = nullptr;
    libvlc_media_player_t* media_player = nullptr;
    std::string path;

    unsigned char* pixel_buffer = nullptr;
    unsigned buffer_size = 0;

    int video_width = 0;
    int video_height = 0;
};

class video_player
{
private:

    libvlc_instance_t* m_instance = nullptr;
    libvlc_media_t* m_media = nullptr;
    libvlc_media_player_t* m_media_player = nullptr;
    libvlc_event_manager_t* event_manager;
    std::unordered_map < std::string, video_data* > videos;



    unsigned char* m_pixel_buffer = nullptr;

    unsigned m_buffer_size = 0;

    int m_video_width = 0;
    int m_video_height = 0;


    bool wait_until_done();
    bool wait_until_done(video_data* video);
    bool parse_media();
    bool parse_media(video_data* video);

    bool extract_video_information();
    bool extract_video_information(video_data* video);

    bool read_video_metadata();
    bool read_video_metadata(video_data* video);

    static void* lock_callback(void* opaque, void** planes);
    static void* lockwa_callback(void* opaque, void** planes);
    static void unlock_callback(void* opaque, void* picture, void* const* planes);
    static void display_callback(void* opaque, void* picture);

public:

    video_player();
    ~video_player();

    bool initialize();

    void load_media(const std::string& media_path, bool loop);

    void load_media(const std::string& media_path, const std::string& media_name, bool loop);

    bool play();
    bool play(const std::string& media_name);

    inline unsigned char* get_video_buffer()
    {
        return m_pixel_buffer;
    }

    inline unsigned char* get_video_buffer(const std::string& media_name)
    {
        return videos[media_name]->pixel_buffer;
    }

    inline int get_video_width()
    {
        return m_video_width;
    }

    inline int get_video_width(const std::string& name_of_video)
    {
        return videos[name_of_video]->video_width;
    }

    inline int get_video_height()
    {
        return m_video_height;
    }

    inline int get_video_height(const std::string& name_of_video)
    {
        return videos[name_of_video]->video_height;
    }

    inline unsigned get_buffer_size()
    {
        return m_buffer_size;
    }
};




