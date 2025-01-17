#ifdef __CCL_XOR__
#define __CCL_XOR__ 

unsigned int CCL_XOR_13L17R5L_32_t(const unsigned int cMax) {  // Xorshift RNG function
    unsigned int Seed = (unsigned int)(std::time(0));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 17;
    Seed ^= Seed << 5;
    
    return Seed % (cMax + 1);
}

#endif