#ifndef __ITEM__
#define __ITEM__

struct sItem
{   // Gun, Shotgun, Sniper, Grenade, Health, Shield
    char * ItemType = nullptr;      // Enum Describe Bit Layout
    void * StructPtr = nullptr;     // Pointer To Item 
}; 

#endif