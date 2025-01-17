#ifndef __HEALTH_ITEM__
#define __HEALTH_ITEM__

// Include ""

struct sHealthItem : sItemOutline
{ 
    unsigned char HealsBy, HealCap, TimeToUse; 
};

#endif