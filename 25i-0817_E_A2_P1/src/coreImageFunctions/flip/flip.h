#pragma once
#include "../../image.h"
#include "../Crop/crop.h"

namespace flipAxis{

   const int flipMatrix[2][2][2] = {
       {
         // reflect around x 
         {1,0},
         {0,-1}
       },

       {
        // reflect around y 

        {-1,0},
        {0,1}
       }

   };


   void flipHorizentally(int &orignalX, int &orignalY, int orignalWidth){
       int pointCoordinates[2] = {orignalX, orignalY};


       int reflectedX = flipMatrix[1][0][0] * pointCoordinates[0] + flipMatrix[1][0][1] * pointCoordinates[1];
       int reflectedY = flipMatrix[1][1][0] * pointCoordinates[0] + flipMatrix[1][1][1] * pointCoordinates[1];

     
       myCrop::crop(reflectedX, reflectedY, orignalWidth - 1, 0);

       orignalX = reflectedX;
       orignalY = reflectedY;
   }

  
   void flipVertically(int &orignalX, int &orignalY, int orignalHeight){
       int pointCoordinates[2] = {orignalX, orignalY};

     
       int reflectedX = flipMatrix[0][0][0] * pointCoordinates[0] + flipMatrix[0][0][1] * pointCoordinates[1];
       int reflectedY = flipMatrix[0][1][0] * pointCoordinates[0] + flipMatrix[0][1][1] * pointCoordinates[1];


       myCrop::crop(reflectedX, reflectedY, 0, orignalHeight - 1);

       orignalX = reflectedX;
       orignalY = reflectedY;
   }
}
