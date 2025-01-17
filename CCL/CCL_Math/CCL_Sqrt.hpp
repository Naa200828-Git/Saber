inline unsigned char CCL_inline_Sqrt(const unsigned short int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}

unsigned char CCL_Sqrt(const unsigned short int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}

unsigned char CCL_Sqrt_32_t(const unsigned int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}

inline unsigned char CCL_inline_Sqrt_32_t(const unsigned int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}

unsigned char CCL_inline_Sqrt_64_t(const unsigned long long int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}

inline unsigned char CCL_inline_Sqrt_64_t(const unsigned long long int cValue) {
    unsigned char Result = 0,
        Bit = 1 << 7;                                // Start with the highest Bit for an 8-Bit Result

    while (Bit > 0) 
    {
        Result |= Bit;
        if (Result * Result > cValue) 
            Result ^= Bit;                          // Remove the Bit if the square is too large
        Bit >>= 1;                                   // Shift to the next Bit
    }
    return Result;
}