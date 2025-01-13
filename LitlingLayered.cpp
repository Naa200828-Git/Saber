#define __NO_SUGAR__ 0 

// Camera centered adjusted by 3/4 tilt angle and lengthen screen, or just have a centerd pos used for rendering Tilted Spirtes    



//
// Is this all the ipsplacment logic, play with the tilt ratio
inline void GetEachTilt(const int UniqueObjAmount, const void* Objects, const void* Positions, const unsigned char EachObjAmount[]) // Could Seperate Into Recalc X&Y Individually
{ 
#if __NO_SUGAR__
    unsigned char LoggedPos = 0, LoggedIterator = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) 
    {
        for(unsigned char l = 0; l < *((unsigned char*)((char*)Objects + (j * 12) + 9)); l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) 
                    + ((*(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) - CameraX) * ((l + 1) 
                        * (*((unsigned char*)((char*)Objects + (i * 12) + 8)))));
                *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) 
                    + ((*(unsigned char*)((char*)(Positions + LoggedIterator + i * 2)) - CameraY) * ((l + 1) 
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

    unsigned char LoggedPos = 0, LoggedIterator = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) // for each type of object, it will work for each layer of that object, then read the stored base positions and then layer by layer calculate the ofset of the layered spite and render it there each frame
    {
        for(unsigned char l = 0; l < LayersAmount; l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                // Display Sprite at 
                BaseX + ((BaseX - CameraX/* - ration for 3/4 top down*/) * ((l + 1) * OffsetPerLayer));
                BaseY + ((BaseY - CameraY/* - ration for 3/4 top down*/) * ((l + 1) * OffsetPerLayer));
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

int main() // Call When Player moved;; Recalculate When Moved
{          // Make Sure to Free Mem

// ~~~~ Should Be sperated Later
    struct LTSprite
    {   
        void** Sprites = nullptr;                
        unsigned char OffsetPerLayer,            
            AmountOfLayers;                      
        // 2-byte padding
    };  // Total, 20 bytes
    const LTSprite* UniqueObjBuffer = new LTSprite[6];
    const void* BaseAdress = GetEachTiltObj(UniqueObjBuffer); // gen in this func then return mem adress int an array??
    const unsigned char TotalObjectAmount = *(unsigned char*)&BaseAdress;
    const unsigned char UniqueObjectAmount = *(unsigned char*)&BaseAdress + 8;

    unsigned char* ObjPositions = new unsigned char[ObjAmount];


    GetEachTilt(UniqueObjAmount, UniqueObjBuffer, Positions, EachObjAmount[]) // Could Seperate Into Recalc X&Y Individually
}

struct LTSprite
{   
    void** Sprites = nullptr;           
    unsigned char OffsetPerLayer,       
        AmountOfLayers;                 
    // 2-byte padding
};  // Total, 20 bytes

inline void* GetLTOnScreen(const void* UniqueObjectBuffer)
{
    unsigned char TotalObjectAmount;
    alignas(1) unsigned char UniqueObjectAmount;
    
    return &TotalObjectAmount; 
}

inline void Once()
{               

// 
    const LTSprite* UniqueObjBuffer = new LTSprite[6];
    const unsigned char* TotalObjectAmount = (unsigned char*)GetLTOnScreen(UniqueObjBuffer),
        UniqueObjectAmount = *(TotalObjectAmount + 8); // dereference toa get that pointer next to it

    const unsigned char* ObjPositionsBuffer = new unsigned char[15];

    while (InGame)
    {
        // ...
        GetEachTilt();
        // ...
    }
}