
#define __NO_SUGAR__ 0 

// + ** Object Tracker from pos entered if faster then grabbing each obbj on screen including already existing ones ** 
// extern cntr + scroll swaps ammo in hotbar for weapon type

inline void LTSprite_Once()
{
// ~~~~ Declarations (to be mvd / rmvd)
struct LayeredTilt_Sprite
{   
    void** Sprites = nullptr;           
    unsigned char Offset,       
        LayersAmount;                 
    // 2-byte padding
};  // Total, 20 bytes
#define LTSprite LayeredTilt_Sprite

constexpr const unsigned char UniqueObj_BuffSize = 6,
    ObjPos_BuffSize = 15;

// ~~~~ Buffers * Declaration
    
    LTSprite UniqueObj_Buff[UniqueObj_BuffSize]; 
    unsigned char ObjPosX_Buff[ObjPos_BuffSize],
        ObjPosY_Buff[ObjPos_BuffSize];

// ~~~~ Size Declarations

    unsigned char UniqueObj_Amount = 1,
        ObjPos_BuffAmount[ObjPos_BuffSize]; 

// ~~~~ Overflow * Declaration
    
    LTSprite* UniqueObj_Overflow = new LTSprite[0];
    unsigned char* ObjPosX_Overflow = new unsigned char[0],
        * ObjPosY_Overflow = new unsigned char[0],
        * ObjPos_Amount_Overflow = new unsigned char[0];

// ~~~~ Single Loop For Test
     
    // If Moved
        // If Objects On Screen

    // Temp:
    int PosX, PosY;
    int CameraX, CameraY_TopDown; 

    for (unsigned char o = 0; o < UniqueObj_Amount; o++)
        for (unsigned char l = 0; l < UniqueObj_Buff[o].LayersAmount; l++)
            for (unsigned char p = 0; p < ObjPos_BuffAmount[o]; p++)
            {
                // ** Display At Instead Of Save, ** The Save Is Temp, ** Is Working On Each Layer 
                PosX = (ObjPosX_Buff[p] - CameraX) * ((l + 1) * UniqueObj_Buff[o].Offset);  
                PosY = (ObjPosY_Buff[p] - CameraY_TopDown) * ((l + 1) * UniqueObj_Buff[o].Offset);
            }
}

int main()
{
    LTSprite_Once();
}