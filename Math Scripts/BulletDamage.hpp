#ifndef __BULLET_DAMAGE__
#define __BULLET_DAMAGE__

inline unsigned char BulletDamage(const int ShotFromX, const int ShotFromY,  const int HitCoordX, const int HitCoordY, const void* LoggedWeapon){    // passing Logge Weapon means must save weapon not directly acsess in arr
    // Calculate the Euclidean distance between two points (ShotFromX, ShotFromY) and (HitCoordX, HitCoordY)
    const short int 
        TriLength = ShotFromX - HitCoordX, // Will never need abs cus pos goes from 0, 0 -> (+)(max), (+)(max)
        TriHeight = ShotFromY - HitCoordY;
    const unsigned char Distance = CCL_inline_Sqrt(TriLength * TriLength + TriHeight * TriHeight);

#if __NO_SUGAR__
    unsigned char TempMax;  // DOES NOT WORK
    for (signed char i = 0; i < *(unsigned short int*)(&LoggedWeapon + 8); i++) // might need start at one
        if (Distance >= *((unsigned short int*)(&LoggedWeapon + 8) + (i + 1)) + i)         // If Fits Within Range
            if (Distance < *((unsigned short int*)(&LoggedWeapon + 8) + (i * 2) + 1))   // ** + i to acount for range naiteration
            {
                TempMax = (*(((unsigned short int*)(&LoggedWeapon + 8) + *(unsigned short int*)(&LoggedWeapon + 8)) + i) & 0b10000000); // is proper way to remove sign?
                if (TempMax) return (Distance / (unsigned char)*((unsigned short int*)(&LoggedWeapon + 8) + (i * 2) + 1)) * ((unsigned char)TempMax); /*Fade ratio w/ Damage*/
                else return *(((unsigned short int*)(&LoggedWeapon + 8) + *(unsigned short int*)(&LoggedWeapon + 8)) + i); // Natural Skip if Range Check false
            }
    // return 0;
#else
    #define BaseAdress (unsigned short int*)(&LoggedWeapon + 6 /*+2 // padding*/) // size of following arr 
    #define Dis1 *(BaseAdress + (i + 1))    // is correct? , 1 2, 2 3, 3 4, ...  
    #define Dis2 *(BaseAdress + (i * 2) + 1) // am moving in pairs ? 
    #define Max  *((BaseAdress + *BaseAdress) + i)  // acsess the memory, pas

    unsigned char UnsignedMax; 
    for (signed char i = 0; i < (*BaseAdress); i++) // might need start at one
        if (Distance > Dis1 + i)         // If Fits Within Range
            if (Distance <= Dis2)   // ** + i to acount for range naiteration
            {
                 UnsignedMax = Max & 0b10000000;
                if (UnsignedMax) return (Distance / (unsigned char)Dis2) * ((unsigned char)UnsignedMax); /*Fade ratio w/ Damage*/
                else return UnsignedMax; // Natural Skip if Range Check false
            }

    #undef BaseAdress 
    #undef Dis1 
    #undef Dis2 
    #undef Max 
#endif
}

#endif