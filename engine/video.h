#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <string>

#include <vlc/vlc.h>

class video_player
{
private:

    libvlc_instance_t* m_instance = nullptr;
    libvlc_media_t* m_media = nullptr;
    libvlc_media_player_t* m_media_player = nullptr;

    unsigned char* m_pixel_buffer = nullptr;

    unsigned m_buffer_size = 0;

    int m_video_width = 0;
    int m_video_height = 0;

private:

    bool wait_until_done();
    bool parse_media();

    bool extract_video_information();
    bool read_video_metadata();

    static void* lock_callback(void* opaque, void** planes);
    static void unlock_callback(void* opaque, void* picture, void* const* planes);
    static void display_callback(void* opaque, void* picture);

public:

    video_player();
    ~video_player();

    bool initialize();

    void load_media(const std::string& media_path);

    bool play();

    inline unsigned char* get_video_buffer()
    {
        return m_pixel_buffer;
    }

    inline int get_video_width()
    {
        return m_video_width;
    }

    inline int get_video_height()
    {
        return m_video_height;
    }

    inline unsigned get_buffer_size()
    {
        return m_buffer_size;
    }
};