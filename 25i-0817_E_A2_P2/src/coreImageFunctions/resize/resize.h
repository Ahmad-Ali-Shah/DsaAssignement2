#pragma once
#include "../../image.h"

/////////////////////////


// scaling for the scaling use scaling standered atrix



///////////////////////////



namespace scaling
{

    static void scale(double targetWidth, double targetHeight, double actualWidth, double actualHeight, int &x, int &y){
        if (targetWidth <= 0 || targetHeight <= 0 || actualWidth <= 0 || actualHeight <= 0)
         return;

        double invScaleX = actualWidth / targetWidth;
        double invScaleY = actualHeight / targetHeight;

        x = static_cast<int>(x * invScaleX);
        y = static_cast<int>(y * invScaleY);

        // Clamp so avoid movement out of box
        if (x < 0)
         x = 0;
        else if (x >= static_cast<int>(actualWidth)) 
         x = static_cast<int>(actualWidth) - 1;

        if (y < 0)
         y = 0;
        else if (y >= static_cast<int>(actualHeight))
         y = static_cast<int>(actualHeight) - 1;
    }
}
