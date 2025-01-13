#define __NO_SUGAR__ 0 


inline unsigned char** GetEachTiltObj()
{

    unsigned char Data[2][]; // Holds Logged Types & 
    // if moved, check every
    // Logged Positions, and Movement substraction to see if left screen, if so, do not re enter obj
    // Have A pointer(mouse) in Buffer Tracker To Put In objs
    // If uniqueObj count > 4
    // then deltet extra created data if drops below 4 and is far away from where player pos was logged

    // Log Types, 0
    // Amount of Each Type, 1

    return Data[2];
}
inline unsigned char GetTiltObjAmount()
{

}

//
// Is this all the ipsplacment logic, play with the tilt ratio
inline void GetEachTilt(const int UniqueObjAmount, const void*& Objects, const void* Positions, const unsigned char EachObjAmount[]) // Could Seperate Into Recalc X&Y Individually
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
    #define Sprite *(void**)((char*)Objects + (i * 12))                        // Start of the 12-byte structure, pointing to the `Sprites` pointer at offset 0
    #define OffsetPerLayer *((unsigned char*)((char*)Objects + (i * 12) + 8))  // Offset 8: `OffsetPerLayer` (after 8 bytes for `Sprites`)
    #define LayersAmount *((unsigned char*)((char*)Objects + (j * 12) + 9))    // Offset 9: `AmountOfLayers` (after 1 byte for `OffsetPerLayer`)
    #define BaseX *(unsigned char*)((char*)(Positions + LoggedIterator + i))
    #define BaseY *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2))


    // 4 A, 6 B, 1 C;; Amount of each object
    // a a a a | b b b b b b | c ;; iterating in positions 
    //      

    // By: By Each Object
        // By: Each Layer
            // By Each Position

    // BaseX = *(unsigned char*)((char*)(Positions + LoggedIterator + i));
    // BaseY = *(unsigned char*)((char*)(Positions + LoggedIterator + i * 2));

    unsigned char LoggedPos = 0, LoggedIterator = 0; // saves pos to acsess in mem from &Positions, cus iterates continuesl in mem, no reset but forl resets
    for (unsigned char j = 0; j < UniqueObjAmount; j++) 
    {
        for(unsigned char l = 0; l < LayersAmount; l++)
            for (unsigned char i = 0; i < EachObjAmount[j]; i++)    // Iterate over each position per object
            {
                // Display Sprite at 
                // Is this it, try diff ways to macro optimize ?
                BaseX + ((BaseX - CameraX) * ((l + 1) * OffsetPerLayer));
                BaseY + ((BaseY - CameraY) * ((l + 1) * OffsetPerLayer));
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
        void* Sprites = nullptr;                 
        unsigned char OffsetPerLayer,            
            AmountOfLayers;                      
        // 2-byte padding
    };  // Total, 20 bytes
    const LTSprite* UniqueObjBuffer = new LTSprite[4];
// ~~~~

    // ** Stop initing Each Time ??
    const ObjGenData[2] = GetEachTiltObj(),
    unsigned char ObjAmount = GetTiltObjAmount(),
        EachObjAmount[UniqueObjAmount]; 
    unsigned char* ObjPositions = new unsigned char[ObjAmount];
    
    if (UniqueObjAmount)
    {        
        GetEachTilt(UniqueObjAmount, UniqueObjBuffer, ObjPositions, EachObjAmount);
    } 
}
