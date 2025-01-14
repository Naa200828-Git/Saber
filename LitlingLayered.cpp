#define __NO_SUGAR__ 0 

// Camera centered adjusted by 3/4 tilt angle and lengthen screen, or just have a centerd pos used for rendering Tilted Spirtes    



// Now Need To Learn Vulkan
// Is this all the ipsplacment logic, play with the tilt ratio
inline void RenderLT(const unsigned char UniqueObjAmount, const void* Objects, const void* Positions, const unsigned char EachObjAmount[]) // Could Seperate Into Recalc X&Y Individually
{ 
#if __NO_SUGAR__
    unsigned char LoggedPos = 0, LoggedIterator = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) 
    {
        for(unsigned char l = 0; l < *((unsigned char*)((char*)Objects + (j * 12) + 9)); l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                LoggedPos++;
                *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) 
                    + ((*(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) - CameraX) * ((l + 1) 
                        * (*((unsigned char*)((char*)Objects + (i * 12) + 8)))));
                *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) 
                    + ((*(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) - CameraY_TopDown) * ((l + 1) 
                        * (*((unsigned char*)((char*)Objects + (i * 12) + 8)))));
            }
        LoggedIterator += LoggedPos; // is best spot for logging iterator
    }
#else
    #define Sprite *(void***)(((char*)Objects + (i * 12) + (l * 8)))                        // Start of the 12-byte structure, pointing to the `Sprites` pointer at offset 0
    #define OffsetPerLayer *((unsigned char*)((char*)Objects + (i * 12) + 8))  // Offset 8: `OffsetPerLayer` (after 8 bytes for `Sprites`)
    #define LayersAmount *((unsigned char*)((char*)Objects + (j * 12) + 9))    // Offset 9: `AmountOfLayers` (after 1 byte for `OffsetPerLayer`)
    #define BaseX *(unsigned char*)((char*)(Positions + LoggedIterator + i))
    #define BaseY *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2))

    unsigned char LoggedIterator = 0, LoggedPos = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) // for each type of object, it will work for each layer of that object, then read the stored base positions and then layer by layer calculate the ofset of the layered spite and render it there each frame
    {
        for(unsigned char l = 0; l < LayersAmount; l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                LoggedPos++;
                // Display Sprite at 
                BaseX + ((BaseX - CameraX) * ((l + 1) * OffsetPerLayer));
                BaseY + ((BaseY - CameraY_TopDown) * ((l + 1) * OffsetPerLayer));
                // Maybe Need remember system so if not moving knows waht to render, of if just leave unchanged render instructions
            }
        LoggedIterator += LoggedPos; // beacuse we navigate position memory unordered by types
    }

    #undef Sprite
    #undef OffsetPerLayer
    #undef LayersAmount 
    #undef BaseX
    #undef BaseY
#endif
}

struct LTSprite
{   
    void** Sprites = nullptr;           
    unsigned char OffsetPerLayer,       
        AmountOfLayers;                 
    // 2-byte padding
};  // Total, 20 bytes

inline short int GetLTOnScreen(const void* UniqueObjectBuffer)
{
    unsigned char TotalObjectAmount,UniqueObjectAmount;
    
    // ~~~~ Logic For
    // ...

    return (TotalObjectAmount << 8) + UniqueObjectAmount;
}

inline void Once()
{               
    // ~~~~ Display Layer Tilit Objects On Screen, No interact, Shadows, Set Up Data
    const LTSprite UniqueObjBuffer[6]; 
    const unsigned char ObjPositionsBuffer[15]

    bool NeedObjPositionsOverflow = ? TotalObjAmount > 15 : 1,  // else 0
        alignas(1) NeedUniqueObjOverflow = ? UniqueObjAmount > 15 : 1;

    alignas(1) unsigned char Temp = GetLTOnScreen(UniqueObjBuffer),
        alignas(1) TotalObjAmount = Temp >> 8, 
        alignas(1) UniqueObjAmount = Temp << 8; 

    if (NeedObjPositionsOverflow)
        alignas(1) unsigned char* ObjPositionsOverflow = new unsigned char[(TotalObjAmount - 15) * 2];
    if (NeedUniqueObjOverflow > 6)
        alignas(1) LTSprite* UniqueObjOverflow = new LTSprite[(TotalObjAmount - 6)];
    while (0) // InGame
    {
        // ...
        // ~~~~ If Player Moved
            // ~~~~ Display Layer Tilit Objects On Screen, No interact, Shadows
        if (NeedObjPositionsOverflow && NeedUniqueObjOverflow)
            RenderLT(UniqueObjAmount, UniqueObjBuffer, ObjPositionsBuffer, TotalObjAmount, ObjPositionsOverflow ,UniqueObjOverflow);
        else if ()
        // ...
    }
}