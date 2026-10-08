#pragma once
////////////////////////////////////


// concept of blur 


//Blur smooths out sharp edges and pixel variations by blending every pixel with its surrounding neighbors.

// it takes the kerrnal radius like to how uch radius we need to blurr

// there are 3 basic ethods of the imager filtering in which Frobenius Matrix Inner Product is one of the best and goated way to do sdo


//////////////////////////////////////
#include <cmath>
#include "../../image.h"

namespace FrobeniusMatrixInnerProductForBlurr{


    // when you have two 1D vectors u and v their relationship is measured using the standard Dot Product

    //When you move from 1D vectors to 2D matrices of the same dimensions their standard dot product is called the Frobenius Matrix Inner Product (written as <A,B>f)


    // norm = sqrt(all values sum of squares)



    // first calculating the product

    inline double frobeniusInnerProduct(const double P[3][3], const double K[3][3]) {
        double sum = 0.0;

        for (int i = 0; i < 3; ++i) {

            for (int j = 0; j < 3; ++j) {

                sum += P[i][j] * K[i][j];

            }

        }

        return sum;
    }

    // clamping the result for thee smooth output 

    inline int clampCoord(int pos, int maxLimit) {

        if (maxLimit <= 0)
            return 0;
        if (pos < 0) 
            return 0;
        if (pos >= maxLimit)
            return maxLimit - 1;

        return pos;
    }

    inline void blurPixel(const double patchR[3][3],  const double patchG[3][3],  const double patchB[3][3],   unsigned int &outR,  unsigned int &outG,   unsigned int &outB) 
    {
        // its not the same kernal btw iie k=Ax=0
        //in calculus when you blur or transform a function f(t) you use an integral transform
        //g(x,y) = integral (k(x,y) * f(y) ) dy here 
        //In calculus, the weighting function k(x,y)
        //was historically named the Integral Kernel 
        //its also called as a Filter Mask, Weight Matrix, or Averaging Window.
        //also we divide 9 to make the same one smoother regardless of darked and darker

        const double K[3][3] = {

            { 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0 },
            { 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0 },
            { 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0 }

        };

        double resR = frobeniusInnerProduct(patchR, K);

        double resG = frobeniusInnerProduct(patchG, K);

        double resB = frobeniusInnerProduct(patchB, K);

        if (resR < 0.0) resR = 0.0; else if (resR > 255.0) resR = 255.0;
        if (resG < 0.0) resG = 0.0; else if (resG > 255.0) resG = 255.0;
        if (resB < 0.0) resB = 0.0; else if (resB > 255.0) resB = 255.0;

        outR = static_cast<unsigned int>(round(resR));

        outG = static_cast<unsigned int>(round(resG));

        outB = static_cast<unsigned int>(round(resB));
        
    }
}
