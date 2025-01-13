#pragma once
#pragma region OverView
// ~~~~ Set Up for Source
// standard library & Custom File Includes
// Macro Definitions (For Now) **
// ToDo List (For Now) **  

// ~~~~ ToDo:
// have sprint method too, that decreases accuracy
// tilteing height things, solid and layed
// and shadowed areas
// solid shadow cloud overcast
// Weird Morphing Storm / Circle, W/ Bubble Shootings from 
//      rim to inside and dying. shrinking at rate, fas completete travel, diff types, ect...

#include <ctime>

#define __NO_SUGAR__ 1 

#pragma endregion
#pragma region CCL
// ~~~~ Champions Cream Library
// Custom Library W/ Tag: 'CCL_' in possesion names
// Contains Possesions: General Algorthims, Layouts, ect..

unsigned int CCL_XOR_13L17R5L_32_t(const unsigned int cMax) {  // Xorshift RNG function
    unsigned int Seed = (unsigned int)(std::time(0));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 17;
    Seed ^= Seed << 5;
    
    return Seed % (cMax + 1);
}

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

template <typename Type> struct CCL_Darr {
    Type* Data = nullptr; // Pointer to dynamically allocated memory
    unsigned short int Size = 5;    // Default size
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


#pragma endregion
#pragma region Item Outline
// ~~~~ Struct Layout of 'Items' & How To Store 
// Needs: FireArms & Heals data filled structs  
// Objects: FireArms, Heals, -> Items

struct sItemOutline
{
    unsigned short int NameSize;
    char * ItemName = nullptr;   
    
    void (*Effect)() = nullptr;
    unsigned char MaxStackAmount;

    // Holding Sprite ** 
    // HotBar Sprite ** 
};

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
struct sHealthItem : sItemOutline
{ 
    unsigned char HealsBy, HealCap, TimeToUse; 
};

struct sItem
{   // Gun, Shotgun, Sniper, Grenade, Health, Shield
    char * ItemType = nullptr;      // Enum Describe Bit Layout
    void * StructPtr = nullptr;     // Pointer To Item 
}; 

#pragma endregion
#pragma region Individual Player Data
// ~~~~ Algorithms
//
//

// ~~~~ Player Facing Mouse Orientation Calculation
//
//

// ~~~~ Bullet Damage Caclulation
//
//
struct sInGamePlayer
{
    sItem HotBar[5];

    unsigned short int * AmmoID = nullptr,
        * AmmoStores = nullptr; // Need Id & amount in short int 
    unsigned char Health = 100, Shield = 0, Sprint = 55;
    // function destructor, not built in destructor 
    int PositionX, PositionY;
};

#pragma endregion
#pragma region Key Algorithms

inline float CalcOrientation(const int MouseX, const int MouseY) {
    if (MouseX == 0 && MouseY == 0) return 0.0f;  // No valid angle; mouse is at the center

    constexpr const float Pi = 3.14159265f,
        TwoPi = 2.0f * Pi;

    float ratio = (float)(MouseY) / (float)(MouseX);
    float AngleRadians;

    if (MouseX > 0)      AngleRadians = ratio / (1.0f + ratio * ratio);       // Approximation of atan for 1st and 4th quadrants
    else if (MouseX < 0) AngleRadians = Pi + ratio / (1.0f + ratio * ratio);  // Adjust by Pi for 2nd and 3rd quadrants   
    else                 AngleRadians = (MouseY > 0) ? Pi / 2.0f : -Pi / 2.0f;// MouseX == 0 (vertical axis)
    
    // Normalize the angle to the range [0, 2*Pi)
    if (AngleRadians < 0.0f) AngleRadians += TwoPi;
    return AngleRadians;
}

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

#pragma endregion
#pragma region Sprite Tiltings

// ~~~~~ Tilting Layered, LT
// Logic: Need Center Point of SCREEN, Not PLayer so we can have dyn. cam. , Ratio To Tilt, Offset by Player
// Object: Each Sprite for Each Layer, Tilt Ratio Adjustment to Emulate Height  

// ~~~~~ Tilting Solid Flat, LSF
// Logic: Need Center Point, Ratio To Tilt, Offset by Player
// Object: Each Sprite for Each Surface / Wall, 

// ~~~~~ Tilting Solid Surface, LSS ** Might just be Lt but tilting to custom ratio
// Logic: Need Center Point, Ratio To Tilt, Offset by Player
// Object: Each Sprite for Each Surface / Wall, 

// ~~~~~ Tilting Layered, LT

// Temp Note, Involves texture Stretching ** Along Straight but shifted Lines
struct LTSprite
{   
    const int TiltRatio;    // Const per Each layer
    const unsigned int BasePosX, BasePosY; 
    const unsigned char OffsetPerLayer;       
    // WIll Display Each Layer At offset insetad of Calulating Offset, Saving, Then Displaying Each Layers of Structs Offset
    const unsigned char AmountOfLayers;
    void* Sprites = nullptr; // Ordered Bottom To Top 
};

// ~~~~~ Tilting Solid Flat, LSF
struct LSFSprite
{
    signed char AmountOfWalls;
    // Like A Wrap Around From North Facing Wall -> West
    // If Amount Of Walls Is Signed, Means A Roof and their would be a +1 Extra Sprite in Arr
    void* Sprites = nullptr;  
};

inline void Calc_LTSprite_Offset(const int CameraPosXY, const unsigned short int Amount, const void* ObjectArr)
{


}


struct LTSprite
{   
    const unsigned short int BasePosX; 
    const unsigned char OffsetPerLayer;       
    const unsigned char AmountOfLayers;
    void* Sprites = nullptr; // Ordered Bottom To Top 
};

void foo()
{
    // array of objects
    
    // Base Position for each partical cast then calculate per cast

    // ~~~~ Partical Casting
    // Will: Take The Object, Have An Amount Of That Object And Where They Are Each
    /* Need:
        Spite Arr for each layer,
        Array Of Base Positions X&Y
        Return OffSet For Each Layer
    */
    
    unsigned char ObjectsAmount; // amount of the objects int he screen / to render;
    long int SpriteTilt[ObjectsAmount];// = Calc_LTSprite_Offset(CameraPosXY, );
}