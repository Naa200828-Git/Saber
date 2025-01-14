#define __NO_SUGAR__ 0 
#define __OVERFLOW__ 0 


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

    // Temp
    int PosX, PosY;
    int CameraX, CameraY_TopDown;

    unsigned char LoggedIterator = 0, LoggedPos = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) // for each type of object, it will work for each layer of that object, then read the stored base positions and then layer by layer calculate the ofset of the layered spite and render it there each frame
    {
        for(unsigned char l = 0; l < LayersAmount; l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                LoggedPos++;
                // Display Sprite at 
                PosX = BaseX + ((BaseX - CameraX) * ((l + 1) * OffsetPerLayer));
                PosY = BaseY + ((BaseY - CameraY_TopDown) * ((l + 1) * OffsetPerLayer));
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

inline void Once()
{               
    // ~~~~ Display Layer Tilit Objects On Screen, No interact, Shadows, Set Up Data
    constexpr const unsigned char UniqueObjBufferSize = 6,
        ObjPositionsBufferSize = 15;

    LTSprite UniqueObjBuffer[UniqueObjBufferSize]; 
    unsigned char ObjPositionsBuffer[ObjPositionsBufferSize];

#if __OVERFLOW__
    #define a8uc_t alignas(1) unsigned char 

// ~~~~ Get LT On Screen

    // Fill Logic
    // ....

    a8uc_t TotalObjAmount; 
    a8uc_t UniqueObjAmount; 

    unsigned char AllObjects[UniqueObjAmount];

    // Fill Logic
    // ....

// ~~~~
#else

    a8uc_t ObjPositionsOverflowSize = (TotalObjAmount > UniqueObjBufferSize) ? (TotalObjAmount - UniqueObjBufferSize) : 0;  // else 0
    a8uc_t UniqueObjOverflowSize = (UniqueObjAmount > ObjPositionsBufferSize) ? (UniqueObjAmount - ObjPositionsBufferSize) : 0;

    a8uc_t* ObjPositionsOverflow = new unsigned char[1];
    alignas(1) LTSprite* UniqueObjOverflow = new LTSprite[1];

    if (ObjPositionsOverflowSize) a8uc_t* ObjPositionsOverflow = new unsigned char[ObjPositionsOverflowSize * 2];
    if (UniqueObjOverflowSize) alignas(1) LTSprite* UniqueObjOverflow = new LTSprite[UniqueObjOverflowSize];
    #undef a8uc_t

#endif

    while (0) // InGame
    {
        // ...
        // ~~~~ If Player Moved
            // ~~~~ Display Layer Tilit Objects On Screen, No interact, Shadows

#if __OVERFLOW__
        RenderLT(UniqueObjAmount, UniqueObjBuffer, ObjPositionsBuffer, AllObjects);
#else
        if (!ObjPositionsOverflowSize && !UniqueObjOverflowSize) 
            RenderLT(UniqueObjAmount, UniqueObjBuffer, ObjPositionsBuffer, AllObjects);
        /*else if (ObjPositionsOverflowSize) 
            unsigned char* ObjPositionsOverflow = new unsigned char[(TotalObjAmount - UniqueObjBufferSize) * 2];
        else if (UniqueObjOverflowSize) 
            RenderLT(UniqueObjAmount, UniqueObjBuffer, ObjPositionsBuffer, TotalObjAmount, UniqueObjOverflowSize, UniqueObjOverflow);
        else if (ObjPositionsOverflowSize && UniqueObjOverflowSize) 
            RenderLT(UniqueObjAmount , UniqueObjBuffer, ObjPositionsBuffer, TotalObjAmount, ObjPositionsOverflow , ObjPositionsOverflowSize, UniqueObjOverflow, UniqueObjOverflowSize, UniqueObjOverflow);
        */
        // If Moved Far enough away
        // if (UniqueObjOverflowSize) delete UniqueObjOverflow[UniqueObjOverflowSize - 1];
        // if (ObjPositionsOverflowSize) delete UniqueObjOverflow[ObjPositionsOverflowSize - 1];
        // ...
#endif
    }
}