#ifndef __FIRE_ARM__
#define __FIRE_ARM__

// #include "" // ** ** After Better Name

struct sFireArm : sItemOutline 
{   /* ** Auto Alignas ** */
    #define A8uc_t alignas(8) unsigned char 
    A8uc_t FireRate;
    A8uc_t Damage;
    A8uc_t AmmoPerRound;
    A8uc_t AmmoLoaded;                             // Could Seperate AmmoLoaded from HotBar ** 
    A8uc_t ReloadTime;                             // In MiliSeconds
    A8uc_t Acuraccy;                               // Rate Per _
    #undef A8uc_t

    // 1 -> 5 = 15, 6 -> 38 = 57, 39 -> 67 = 89 (9  bytes)
    // 1 -> 5, -> -38, -> 67,
    //  w/ 15, 57, 89, (7 bytes)
    alignas(8) unsigned short int AmountOfRanges;                  
    alignas(8) unsigned short int * DamageRanges = nullptr;        
};

#endif