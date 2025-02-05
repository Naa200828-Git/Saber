#ifndef __CCL_DARR__
#define __CCL_DARR__

template <typename Type> struct CCL_Darr {
    Type* Data = nullptr; // Pointer to dynamically allocated memory
    unsigned short int Size = 1;    // Default size
};

#endif