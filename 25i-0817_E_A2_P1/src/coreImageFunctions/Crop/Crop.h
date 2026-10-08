/*

croping is nothing but a proper translation

It is pure translation of the origin: the orign 
(0,0) -> (x0,y0)


so solving ts by proper standered matrix of translation

*/

#pragma once
#include "../../image.h"

namespace myCrop{
         
    void crop(int &orignalX , int & orignalY , int extendedX , int extendedY){


        /////////////////////////////

        // standered matrix of a 

        ///////////////////////////


        int standeredXytrnaslationMatrix[3][3] = {{1,0,extendedX} , {0,1,extendedY} , {0,0,1}};

        //////////////////////////

        // took points as the point matrix

        /////////////////////////////


        int pointCoordinates[3] = {orignalX , orignalY , 1};


        // Direct O(1) evaluation derived from matrix-vector multiplication
        pointCoordinates[0] = (pointCoordinates[0] + standeredXytrnaslationMatrix[0][2]); // x+a

        pointCoordinates[1] = (pointCoordinates[1] + standeredXytrnaslationMatrix[1][2]); // y+b

        pointCoordinates[2] = 1;



        orignalX = pointCoordinates[0];

        orignalY = pointCoordinates[1];


        // values got changed 
    }
}
