// Choose Start And End Point From Non Opposing Halfs Of Each Face

// Select a # with a curve, Take A Path Distance
// Select a # from 1-4 Take A Direction

// Go From Each End Point Until Over Lap Of Paths 

#include <ctime>

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

int main()
{   
    #define Sized_Int unsigned int    
    constexpr const Sized_Int ccMaze_SizeX = 100,
        ccMaze_SizeY = 150,
        MaxPath_Size = (ccMaze_SizeX + ccMaze_SizeY / 2) * 0.1;   
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

    struct sPath
    {
        Sized_Int Length;
        unsigned char Direction;
    };
    
    struct CCL_Full_Darr { // split into sperate functions that take & params for functions
        sPath* Data;
        Sized_Int Size;
        Sized_Int Capacity;

        CCL_Full_Darr() : Data(nullptr), Size(0), Capacity(0) {}

        ~CCL_Full_Darr() {
            delete[] Data;
        }   

        void push_back(const sPath& Item) 
        {
            if (Size == Capacity) 
            {
                Capacity = (Capacity == 0) ? 1 : Capacity * 2;
                sPath* newData = new sPath[Capacity];
                
                for (Sized_Int i = 0; i < Size; ++i) 
                    newData[i] = Data[i];

                delete[] Data;
                Data = newData;
            }
            Data[Size++] = Item;
        }

        sPath& operator[](Sized_Int Index) {
            return Data[Index];
        }
    };

    CCL_Full_Darr PathFromStart,
        PathFromEnd;

    while (Connected) // maybe put reset at begining and do not init with reset functions
    {
// ~~~~ Fill Path
        // Fill 
        // set PathPos's
// ~~~~ Reset
        PathFromStart[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromStart[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        PathFromStart[Connected].Length = CCL_XOR_13L17R5L_32_t(MaxPath_Size);
        PathFromStart[Connected].Direction = CCL_XOR_13L17R5L_32_t(4);

        if (PathPosX[0], PathPosX[1], PathPosY[0], PathPosY[1]) break; // If Connected
        Connected++;
    }
// ~~~~ Maze Finished Generating
}

