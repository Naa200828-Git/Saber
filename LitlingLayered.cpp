#define __NO_SUGAR__ 0 


inline void GetEachTilt(const int Amount, const void* Objects, const void* Positions)
{   

#if __NO_SUGAR__
#else
    #define Sprite *(void**)(Objects + i)                     
    #define BasePosX *(unsigned int*)((char*)Objects + (i * 20) + 8) 
    #define BasePosY *(unsigned int*)((char*)Objects + (i * 20) + 12)
    #define OffsetPerLayer *((unsigned char*)((char*)Objects + (i * 20) + 16))
    #define LayersAmount *((unsigned char*)((char*)Objects + (i * 20) + 17))
    #define ParticalsAmount *(*(unsigned char**)((char*)Positions + i * sizeof(unsigned char*)))
    
    for (unsigned char i = 0; i < Amount; i++)                  // Amount Of Objects
        for (unsigned char j = 0; j < LayersAmount; j++)        // Amount Of Layers
            for (unsigned char l = 0; l < ParticalsAmount; l++) // Amount Of Particals To Calc OffSet


    #undef Sprite
    #undef BasePosX
    #undef BasePosY
    #undef OffsetPerLayer
    #undef LayersAmount 
    #undef ParticalsAmount 
#endif
}

int main()
{
    struct LTSprite
    {   
        void* Sprites = nullptr;                
        alignas(4) unsigned int BasePosX, BasePosY; 
        unsigned char OffsetPerLayer, AmountOfLayers;           
        // 2-byte Padding
    };  // 20 Bytes Total

    int UniqueObjAmount;
    LTSprite* UniqueObj = new LTSprite[UniqueObjAmount];
    unsigned char** ObjBasePositions = new unsigned char*[UniqueObjAmount]; // First Byte After Tells You Amount Of Base Positions
    GetEachTilt(UniqueObjAmount, UniqueObj, ObjBasePositions);
}