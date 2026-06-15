#include "headers/subtexture.h"




//void subtexture::texturecoordinates(glm::vec2 indices, glm::vec2* coordinates)
//{
//    // 1. Pixel Positions nikaalo
//    

glm::vec4 subtexture::texturecoordinates(glm::vec2 indices, float tile_width, float tile_height, float sheetheight, float sheetwidth)
{
    float min_x = (indices.x * tile_width);
    float min_y = (indices.y * tile_height);
    float max_x = ((indices.x + 1) * tile_width);
    float max_y = ((indices.y + 1) * tile_height);

    // 2. Normalize (Divide by SHEET dimensions, not sprite dimensions)
    // Ye line sabse important hai:
    coordinates.y = { min_y / sheetheight }; // BL
    coordinates.x = { min_x / sheetwidth }; // BL
    coordinates.z = { max_x / sheetwidth }; // TR
    coordinates.a = { max_y / sheetheight }; // TR

    //coordinates[0].y = { max_x / sheetwidth, min_y / sheetheight }; // 
    //coordinates[1].y = { min_x / sheetwidth, max_y / sheetheight }; // TL

    std::cout << "DEBUG: Sheet Size: " << sheetwidth << "x" << sheetheight << std::endl;
    if (sheetwidth == 0 || sheetheight == 0) __debugbreak(); // Yahan phata toh matlab texture load nahi hui

    return  coordinates;
}
