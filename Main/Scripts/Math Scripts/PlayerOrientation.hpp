#ifndef __PLAYER_ORIENTATION__
#define __PLAYER_ORIENTATION__

inline float CalcOrientation(const int MouseX, const int MouseY) {
    if (MouseX == 0 && MouseY == 0) return 0.0f;  // No valid angle; mouse is at the center

    constexpr const float Pi = 3.14159265f,
        TwoPi = 2.0f * Pi;

    float ratio = (float)(MouseY) / (float)(MouseX),
        AngleRadians;

    if (MouseX > 0)      AngleRadians = ratio / (1.0f + ratio * ratio);       // Approximation of atan for 1st and 4th quadrants
    else if (MouseX < 0) AngleRadians = Pi + ratio / (1.0f + ratio * ratio);  // Adjust by Pi for 2nd and 3rd quadrants   
    else                 AngleRadians = (MouseY > 0) ? Pi / 2.0f : -Pi / 2.0f;// MouseX == 0 (vertical axis)
    
    // Normalize the angle to the range [0, 2*Pi)
    if (AngleRadians < 0.0f) AngleRadians += TwoPi;
    return AngleRadians;
}

#endif