// Choose Start And End Point From Non Opposing Halfs Of Each Face

// Select a # with a curve, Take A Path Distance
// Select a # from 1-4 Take A Direction

// Go From Each End Point Until Over Lap Of Paths 

#include <ctime>

// #define __LEIGHTWHEIGHT_OR_FAST__ 0 // for asm,  -Og / Os, O3 
#define Sized_Int unsigned int    

constexpr const Sized_Int ccMaze_SizeX = 100,
    ccMaze_SizeY = 150,
    MaxPath_Size = (ccMaze_SizeX + ccMaze_SizeY / 2) * 0.1;   

unsigned int CCL_XOR_13L17R5L_32_t(const unsigned int cMax) {
    unsigned int Seed = (unsigned int)(std::time(NULL));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 5;
    
    return Seed % (cMax + 1);
}
bool CCL_TF() {  // Maybe Make inline
    unsigned int Seed = (unsigned int)(std::time(NULL));
    return Seed & 0b1;
}

struct alignas(1) sPath
{
    Sized_Int Length;      
    unsigned char Direction;
};
    
struct CCL_Darr {
    sPath* Data = nullptr; // Pointer to dynamically allocated memory
    unsigned short int Size = 1;    // Default size
}; 
void CCL_Darr_cAdjSize(CCL_Darr& Arr, const unsigned char cAdjSize) {
    const unsigned short int NewSize = Arr.Size + cAdjSize; // Increase size
    sPath* NewData = new sPath[NewSize]; // Allocate new memory

    // Copy existing elements to new memory
    for (unsigned short int i = 0; i < Arr.Size; ++i) 
        NewData[i] = Arr.Data[i];

    // Initialize new elements
    for (unsigned short int i = Arr.Size; i < NewSize; ++i) 
        NewData[i] = sPath();

    // Free old memory
    delete[] Arr.Data;

    // Update the array
    Arr.Data = NewData;
    Arr.Size = NewSize;
}
void CCL_Darr_Free(CCL_Darr& Arr) {
    delete[] Arr.Data; // Free the memory
    Arr.Data = nullptr;
    Arr.Size = 0;
};

inline bool GenerateMaze()
{   // maybe make for-loop?
// ~~~~ Choose End Points
    Sized_Int Connected = CCL_TF(),
        StartPoint; 

    if (Connected) StartPoint = CCL_XOR_13L17R5L_32_t(ccMaze_SizeX >> 2) + 1;
    else           StartPoint = (CCL_XOR_13L17R5L_32_t(ccMaze_SizeX >> 2) * 2) - 1;

    Sized_Int PathPosStart[2];
    if (Connected) 
    {
        PathPosStart[0] = 0; 
        PathPosStart[1] = StartPoint; 
    }
    else   
    {
        PathPosStart[0] = StartPoint; 
        PathPosStart[1] = ccMaze_SizeY; 
    }

    Connected = CCL_TF();
    Sized_Int EndPoint;
    if (Connected) EndPoint = CCL_XOR_13L17R5L_32_t(ccMaze_SizeY >> 2) + 1;
    else           EndPoint = (CCL_XOR_13L17R5L_32_t(ccMaze_SizeY >> 2) * 2) - 1;

    Sized_Int PathPosEnd[2];
    if (Connected) 
    {
        PathPosEnd[0] = EndPoint;     
        PathPosEnd[1] = ccMaze_SizeX; 
    }
    else
    {
        PathPosEnd[0] = 0;            
        PathPosEnd[1] = EndPoint;     
    }
// ~~~~ Bridge
    Sized_Int Path = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
    signed char Direction = CCL_XOR_13L17R5L_32_t(4);

    CCL_Darr PathFromStart,
        PathFromEnd;

    Connected = 0;
    while (1) // maybe put reset at begining and do not init with reset functions
    {
// ~~~~ Fill Path
        // set PathPos's
// ~~~~ Reset
        CCL_Darr_cAdjSize(PathFromStart, Connected); 
        PathFromStart.Data[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromStart.Data[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        CCL_Darr_cAdjSize(PathFromEnd, Connected);
        PathFromEnd.Data[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromEnd.Data[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        // What if connects with a previous path ** Will continue until front path connection. Keep that way, i like better
        for (unsigned char i = 0; i < PathFromStart.Data[Connected].Length; i++)
            if (PathPosEnd[0] == PathPosStart[0] && PathPosStart[1] == PathPosEnd[1]) break; // If Connected, ** Turn into chain for opt

        Connected++;
    }
// ~~~~ Maze Finished Generating
    return 0;
}

int main()
{
    return GenerateMaze();
}