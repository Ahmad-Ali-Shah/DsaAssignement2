#pragma once
#include <cmath>
#include "../../image.h"

// Grayscale conversion using standard ITU-R BT.709 luminance weights
// Dot product: Y = 0.2126*R + 0.7152*G + 0.0722*B
namespace MygreyScale{

    void greyScale(double &R , double &G , double &B){

        // Luminance dot product: w^T * c 

        double  Result = 0.2126*R+0.7152*G+0.0722*B;

        R = round(Result);
        G = round(Result);
        B = round(Result);
    }

    // Overload for unsigned int channels (matching brightness.h and image pixels)
    void greyScale(unsigned int &R , unsigned int &G , unsigned int &B){

        double Result = 0.2126 * static_cast<double>(R) + 0.7152 * static_cast<double>(G) + 0.0722 * static_cast<double>(B);

        unsigned int gray = static_cast<unsigned int>(round(Result));
        R = gray;
        G = gray;
        B = gray;
    }
}
