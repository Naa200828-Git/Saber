#ifndef __ITEM_OUTLINE__
#define __ITEM_OUTLINE__

struct sItemOutline // mybe use buffer for faster acsess
{
    unsigned short int NameSize;
    char * ItemName = nullptr;   
    
    void (*Effect)() = nullptr;
    unsigned char MaxStackAmount;

    // Holding Sprite ** 
    // HotBar Sprite ** 
};

#endif