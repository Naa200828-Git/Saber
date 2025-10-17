#include "AllIncludes.hpp"

#pragma region CCL

#pragma region Darr
        // ~~~ Custom Vector w/ +2 Adj 
    template <typename Type> struct CCL_Darr {            // Using OOP, Heap Allocated, expandble, minimal Arr, w/ <typedef>  
        Type * Data = nullptr;                            // Pointer to dynamically allocated memory
        uint16_t Size = 1;
    };
        // ~~~ Base Function: Arr Size += 2:
    template <typename Type> void CCL_Darr_cAdjSize(CCL_Darr<Type> & Arr, const uint_least8_t cAdjSize) {
        const uint_least16_t NewSize = Arr.Size + cAdjSize;  // Increase size by #
        Type * NewData = new Type[NewSize];                  // Allocate new memory
  
        for (int i = Arr.Size; i < NewSize; ++i)   
            NewData[i] = Type();  
  
        Arr.Data = NewData;                                  // Point to the new data
        Arr.Size = NewSize;                                  // Update the size
    }      
        // ~~~ Free CCL_Darr mem
    template <typename Type> void CCL_Darr_Free(CCL_Darr<Type>& Arr) {
        delete[] Arr.Data;
        Arr.Data = nullptr;
        Arr.Size = 0; // ** 
    }
#pragma endregion
#pragma region Rand


#if __USE_EXPERIMENTAL__ && !__HIGHER_ENTROPY__

    uint32_t CCL_XOR_13L17R5Lecti_32_t(const uint32_t cMax, ...) {  // Xorshift RNG function
        uint32_t Seed = (uint32_t)(std::time(0));
        Seed ^= Seed << 13;
        Seed ^= Seed >> 17;
        Seed ^= Seed << 5;

        Seed = Seed % (cMax + 1);

        if (&cMax + 8) 
            return Seed;
        else CCL_XOR_13L17R5L_32_t(Seed, 0); // ~~~~ Higher Entropy, use goto?
    }
    #define CCL_XOR_13L17R5Lecti_32_t CCL_XOR_13L17R5L_32_t // legacy

#elif !__HIGHER_ENTROPY__

    uint32_t CCL_XOR_13L17R5L_32_t(const uint32_t cMax) {  // Xorshift RNG function
        uint32_t Seed = (uint32_t)(std::time(0));
        Seed ^= Seed << 13;
        Seed ^= Seed >> 17;
        Seed ^= Seed << 5;

        return Seed % (cMax + 1);
    }

#else

    uint32_t CCL_XOR_13L17R5L_32_t(const uint32_t cMax) {  
        uint32_t Seed = (uint32_t)(std::time(0));
        Seed ^= (uint32_t)(std::time(0)) && 0b1111;
                                  // Combine time-based entropy with random device entropy
        Seed ^= Seed << 13;       // Xorshift with more entropy mixing
        Seed ^= Seed >> 17;
        Seed ^= Seed << 5;
        
        Seed ^= Seed >> 3;        // More bit manipulation for additional entropy
        Seed ^= Seed << 21;
        Seed ^= Seed >> 4;

        return Seed % (cMax + 1); // Return the value in the range [0, cMax]
    }

#endif
        // ~~~ T/F Rand
    #define CCL_TFRand CCL_XOR_13L17R5L_32_t(1)
    #define CCL_Rand(cMax) CCL_XOR_13L17R5L_32_t(cMax)

#pragma endregion
#pragma endregion