#define __NO_SUGAR__ 0 


inline unsigned char GetEachTiltObj()
{
    // if moved, check every
    // Logged Positions, and Movement substraction to see if left screen, if so, do not re enter obj
    // Have A pointer(mouse) in Buffer Tracker To Put In objs
    // If Onj count > 30

    // Log Types Only
}
inline unsigned char GetTiltObjAmount()
{

}
// this shi so abstract
inline void GetEachTilt(const int Amount, const void* Objects, const void* Positions) // Could Seperate Into Recalc X&Y Individually
{   
#if __NO_SUGAR__
#else
    #define Sprite *(void**)((char*)Objects + (i * 12))                        // Start of the 12-byte structure, pointing to the `Sprites` pointer at offset 0
    #define OffsetPerLayer *((unsigned char*)((char*)Objects + (i * 12) + 8))  // Offset 8: `OffsetPerLayer` (after 8 bytes for `Sprites`)
    #define LayersAmount *((unsigned char*)((char*)Objects + (i * 12) + 9))    // Offset 9: `AmountOfLayers` (after 1 byte for `OffsetPerLayer`)
    #define ParticalsAmount  // Describes The Amount Of bytes * 2, (X&Y Pos allocated)

    // 2d array of each object
    for (unsigned char p = 0; p < ParticalsAmount; p++) // Amount Of Particals To Calc OffSet
    {
        
    }

    return

    #undef Sprite
    #undef OffsetPerLayer
    #undef LayersAmount 
    #undef ParticalsAmount
#endif
}

int main() // Call When Player moved 
{

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
    unsigned char UniqueObjAmount = GetEachTiltObj(),
        ObjAmount = GetTiltObjAmount();
    unsigned char* ObjPositions = new unsigned char[ObjAmount];
    // Do You Need Complicated arr & Vector, or is better to have a Total amount of Positions, and a for loop that acsess at:
    // [j] // j is goes from 0 - UniqueObjAmount; in an array of Unique Objects;, so its like this: a a a a a | b b b b | c c | d ...
    // It will know By the amount of each obj to then go to the next index for j, so auto acounts for sprite displaying
    if (UniqueObjAmount)
    {        
        GetEachTilt(UniqueObjAmount, UniqueObjBuffer, ObjPositions);
    } 
}
