#ifndef __LTSPRITE__
#define __LTSPRITE__

#include "Includes Code\Structs\Sprites\Z-TilitSprite.hpp"
#include "Main\Includes\CompileOptions.hpp"

#define LTSprite LayeredTilt_Sprite

// ~~~~ Temp
int PosX, PosY,
    CameraX, CameraY_TopDown; 

inline void Get_LTSprite_SizeDeclartions() // change name to [...] get amounts
{// If Moved
    // Search Through chunk  Of Close By Allocated Objects, Count Amount of !nullptrs
    // The Stack buffer

    // if num > max ... OverFlow handle
}
inline void Render_LTSprite(
    const unsigned char& UniqueObj_Amount, 
    const LTSprite UniqueObj_Buff[ccUniqueObj_BuffSize], 
    const unsigned char ObjPos_BuffAmount[ccObjPos_BuffSize],
    const unsigned char ObjPosX_Buff[ccObjPos_BuffSize],
    const unsigned char ObjPosY_Buff[ccObjPos_BuffSize]
){// If Moved
    // If Objects On Screen
    for (unsigned char o = 0; o < UniqueObj_Amount; o++)
        for (unsigned char l = 0; l < UniqueObj_Buff[o].LayersAmount; l++)
            for (unsigned char p = 0; p < ObjPos_BuffAmount[o]; p++)
            {
                // ** Display At Instead Of Save, ** The Save Is Temp, ** Is Working On Each Layer 
                PosX = (ObjPosX_Buff[p] - CameraX) * ((l + 1) * UniqueObj_Buff[o].Offset);  
                PosY = (ObjPosY_Buff[p] - CameraY_TopDown) * ((l + 1) * UniqueObj_Buff[o].Offset);
            }
}
inline void LTSprite_Once()
{// ~~~~ Buffers * Declaration
    LTSprite UniqueObj_Buff[ccUniqueObj_BuffSize]; 
    unsigned char ObjPosX_Buff[ccObjPos_BuffSize],
        ObjPosY_Buff[ccObjPos_BuffSize];
// ~~~~ Size Declarations
    unsigned char UniqueObj_Amount,
        ObjPos_BuffAmount[ccObjPos_BuffSize]; 
// ~~~~ Overflow * Declaration
#if __ZTILT_OVERFLOW_HANDLING__ 
    LTSprite* UniqueObj_Overflow = new LTSprite[1];
    unsigned char* ObjPosX_Overflow = new unsigned char[1],
        * ObjPosY_Overflow = new unsigned char[1],
        * ObjPos_Amount_Overflow = new unsigned char[1];
#endif
// ~~~~ Single Loop For Test
    Render_LTSprite(UniqueObj_Amount, UniqueObj_Buff, ObjPos_BuffAmount,ObjPosX_Buff,ObjPosY_Buff);
}

#endif