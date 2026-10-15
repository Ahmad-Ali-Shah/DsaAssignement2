/*

Brightness adjustment applied across all points:
Translating color coordinates in the RGB cube.

Color as a Vector in a 3D Vector Space:
Every pixel is represented as a 3D color vector.
The set of all possible displayable colors forms a bounded geometric 3D cube called the RGB Color Cube.

Brightness adjustment is an Affine Vector Translation along the Gray Diagonal Vector.
*/

#pragma once
#include "../../image.h"

namespace MyBrightness{


    double clampValue(unsigned int orignalValue, double delta){

        double newVal = static_cast<double>(orignalValue) + delta;

        if(newVal > 255.0){
            newVal = 255.0;
        }
        else if(newVal < 0.0){
            newVal = 0.0;
        }

        return newVal;
    }

    void brightness(unsigned int &r , unsigned int &g  , unsigned int& b, double delta ){

        r = static_cast<unsigned int>(clampValue(r, delta));
        g = static_cast<unsigned int>(clampValue(g , delta));
        b = static_cast<unsigned int>(clampValue(b , delta));


        // Color channels treated as spatial coordinates in the RGB color cube

    }
}
