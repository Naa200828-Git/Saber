#ifdef __CCL_DARR_FREE__
#define __CCL_DARR_FREE__

template <typename Type> void CCL_Darr_Free(CCL_Darr<Type>& Arr) {
    delete[] Arr.Data; // Free the memory
    Arr.Data = nullptr;
    Arr.Size = 0;
}

#endif