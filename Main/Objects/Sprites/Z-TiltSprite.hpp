#ifndef __LTSPRITE_STRUCT__
#define __LTSPRITE_STRUCT__

struct LayeredTilt_Sprite
{   
    void** Sprites = nullptr;   
#if __TEMP_HIGH_VIS_QUALITY__
    void** LightMap = nullptr;   
#endif
    unsigned char Offset,       
        LayersAmount;                 
    // 2-byte padding
};  // Total, 20 bytes

#endif 