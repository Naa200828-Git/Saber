#include <ifstream>

template <typename Type> struct CCL_Darr {
    Type* Data = nullptr; 
    unsigned short int Size = sizeof(Type);
};

// Adjust the size of the array
template <typename Type> void CCL_Darr_cAdjSize(CCL_Darr<Type>& Arr, const unsigned char cAdjSize) {
    const unsigned short int NewSize = Arr.Size + cAdjSize; // Increase size
    Type* NewData = new Type[NewSize]; // Allocate new memory

    // Copy existing elements to new memory
    for (unsigned short int i = 0; i < Arr.Size; ++i) 
        NewData[i] = Arr.Data[i];

    // Initialize new elements
    for (unsigned short int i = Arr.Size; i < NewSize; ++i) 
        NewData[i] = Type();

    // Free old memory
    delete[] Arr.Data;

    // Update the array
    Arr.Data = NewData;
    Arr.Size = NewSize;
}

// Free dynamically allocated memory
template <typename Type> void CCL_Darr_Free(CCL_Darr<Type>& Arr) {
    delete[] Arr.Data; // Free the memory
    Arr.Data = nullptr;
    Arr.Size = 0;
}

struct sFruit
{
    CCL_Darr<char> FruitName;
    double Price; 
};
inline bool ReadFruitFile(const char* FruitFile)
{
// ~~~~ Read
    std::ifstream FRUIT_FILE(FilePath, std::ios::binary);
    unsigned char Temp;

    CCL_Darr<sFruit> ListedFruit;
    FRUIT_FILE.read(&Temp, 1);  // Amount Of Fruit In File
    CCL_Darr_cAdjSize(&ListedFruit, Temp);

    for (unsigned char i = 0; i < Temp; i++)
    {   
        FRUIT_FILE.read(&Temp, 1);  // Amount Of Letters In Fruit Name
        CCL_Darr_cAdjSize(&ListedFruit[i].FruitName, Temp);
        FRUIT_FILE.read(&ListedFruit[i].FruitName[i], Temp);  // Amount Of Letters In Fruit Name
        FRUIT_FILE.read(&ListedFruit[i].Price, 2); 
    }

// ~~~~ End
    for (unsigned char i = 0; i < Temp; i++)
        CCL_Darr_Free(&ListedFruit[i].FruitName); // where is szie to delete declared?
    CCL_Darr_Free(&ListedFruit); // where is szie to delete declared?

    return 0;
}
int main()
{
    constexpr const char* FilePath = "";    
    // Structered like [#Letters in Name][Name][Mint Price]
    return ReadFruitFile(FilePath);
}

