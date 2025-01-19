#ifndef __CCL_DARR_CADJSIZE__
#define __CCL_DARR_CADJSIZE__

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

#endif