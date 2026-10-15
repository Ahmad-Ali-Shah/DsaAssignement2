/*

Cropping corresponds to an affine translation of the origin:
(0,0) -> (x0,y0)

Solved using the standard 3x3 translation affine matrix.
*/

#pragma once
#include "../../image.h"

namespace myCrop{
         
    void crop(int &orignalX , int & orignalY , int extendedX , int extendedY){


        /////////////////////////////

        // Standard 3x3 homogeneous translation matrix

        ///////////////////////////


        int standardTranslationMatrix[3][3] = {{1,0,extendedX} , {0,1,extendedY} , {0,0,1}};

        //////////////////////////

        // Homogeneous coordinate vector

        /////////////////////////////


        int pointCoordinates[3] = {orignalX , orignalY , 1};


        // Direct O(1) evaluation derived from matrix-vector multiplication
        pointCoordinates[0] = (pointCoordinates[0] + standardTranslationMatrix[0][2]); // x+a

        pointCoordinates[1] = (pointCoordinates[1] + standardTranslationMatrix[1][2]); // y+b

        pointCoordinates[2] = 1;



        orignalX = pointCoordinates[0];

        orignalY = pointCoordinates[1];


        // Coordinates translated successfully
    }
}
