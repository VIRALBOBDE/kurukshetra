#include "headers/subtexture.h"


subtexture::subtexture(texture& tex, glm::vec2 tiledim) : l_texture(tex), sheetheight((float)tex.getheight()),
sheetwidth((float)tex.getwidth()), spriteheight((float)tiledim.y), spritewidth((float)tiledim.x), tileheight(sheetheight / spriteheight)
{
    std::cout << "DEBUG: Sheet Size: " << sheetwidth << "x" << sheetheight << std::endl;
    if (sheetwidth == 0 || sheetheight == 0) __debugbreak(); // Yahan phata toh matlab texture load nahi hui
}
void subtexture::texturecoordinates(glm::vec2 indices, glm::vec2* coordinates)
{
    // 1. Pixel Positions nikaalo
    float min_x = (indices.x * spritewidth);
    float min_y = (indices.y * spriteheight);
    float max_x = ((indices.x + 1) * spritewidth);
    float max_y = ((indices.y + 1) * spriteheight);

    // 2. Normalize (Divide by SHEET dimensions, not sprite dimensions)
    // Ye line sabse important hai:
    coordinates[0] = { min_x / sheetwidth, min_y / sheetheight}; // BL
    //coordinates[0].y = { max_x / sheetwidth, min_y / sheetheight }; // BR
    coordinates[1] = { max_x / sheetwidth, max_y / sheetheight }; // TR
    //coordinates[1].y = { min_x / sheetwidth, max_y / sheetheight }; // TL
}

