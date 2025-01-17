#ifndef __IN_GAME_PLAYER__
#define __IN_GAME_PLAYER__

struct sInGamePlayer
{
    sItem HotBar[5];
    sAmmo Ammo_HotBar[5]; // first five can be CNTRL + Scrolled Through For Weapon Type 
    sAmmo * AmmoStores = nullptr; 

    unsigned char Health = 100, Shield = 0, Sprint = 35;
    // function destructor, not built in destructor 
    int PosX, PosY; // make type consistant
};

#endif