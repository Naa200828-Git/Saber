// Choose Start And End Point From Non Opposing Halfs Of Each Face

// Select a # with a curve, Take A Path Distance
// Select a # from 1-4 Take A Direction

// Go From Each End Point Until Over Lap Of Paths 

#include <ctime>

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
{   
// ~~~~ Choose End Points
    Sized_Int Connected = CCL_TF();

    Sized_Int StartPoint;  
    if (Connected) StartPoint = CCL_XOR_13L17R5L_32_t(ccMaze_SizeX >> 2) + 1;
    else           StartPoint = (CCL_XOR_13L17R5L_32_t(ccMaze_SizeX >> 2) * 2) - 1;

    Sized_Int EndPoint;
    if (Connected) EndPoint = CCL_XOR_13L17R5L_32_t(ccMaze_SizeY >> 2) + 1;
    else           EndPoint = (CCL_XOR_13L17R5L_32_t(ccMaze_SizeY >> 2) * 2) - 1;

    bool StartPoint_Face = CCL_TF(),
        EndPoint_Face = CCL_TF();
// ~~~~ Bridge
    Connected = 0;

    Sized_Int PathPosX[2], PathPosY[2],
        Path = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
    signed char Direction = CCL_XOR_13L17R5L_32_t(4);

    CCL_Darr PathFromStart,
        PathFromEnd;

    while (1) // maybe put reset at begining and do not init with reset functions
    {
// ~~~~ Fill Path
        // Fill 
        // set PathPos's
// ~~~~ Reset
        CCL_Darr_cAdjSize(PathFromStart, 1);

        PathFromStart.Data[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromStart.Data[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        CCL_Darr_cAdjSize(PathFromEnd, 1);

        PathFromEnd.Data[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromEnd.Data[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        if (PathPosX[0], PathPosX[1], PathPosY[0], PathPosY[1]) break; // If Connected
        Connected++;
    }
// ~~~~ Maze Finished Generating
    return 0;
}

int main()
{
    return GenerateMaze();
}