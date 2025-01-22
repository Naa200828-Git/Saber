// Choose Start And End Point From Non Opposing Halfs Of Each Face

// Select a # with a curve, Take A Path Distance
// Select a # from 1-4 Take A Direction

// Go From Each End Point Until Over Lap Of Paths 

#include <ctime>

unsigned int CCL_XOR_13L17R5L_32_t(const unsigned int cMax) {
    unsigned int Seed = (unsigned int)(std::time(0));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 5;
    
    return Seed % (cMax + 1);
}
bool CCL_TF() {  // Xorshift RNG function
    unsigned int Seed = (unsigned int)(std::time(0));
    return Seed & 0b1;
}

int main()
{   
    #define Sized_Int unsigned int    
    constexpr const Sized_Int ccMaze_SizeX = 100,
        ccMaze_SizeY = 150,
        MaxPath_Size = (ccMaze_SizeX + ccMaze_SizeY / 2) * 0.1;   
// ~~~~ Choose End Points
    bool Connected = CCL_TF();

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

    struct sPath
    {
        Sized_Int Length;
        unsigned char Direction;
    };
    
    sPath* PathFromStart = new sPath[1],
        * PathFromEnd = new sPath[1];

    while (!Connected)
    {
// ~~~~ Fill Path
        // how does this work as vector / arr
        // assign

// ~~~~ Reset ** Maybe just fill in data from location
        PathFromStart -> Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromStart -> Direction = CCL_XOR_13L17R5L_32_t(4);

        if (PathPosX[0], PathPosX[1], PathPosY[0], PathPosY[1]) break; // If Connected
    }

}