#pragma once
#include "../../image.h"
#include "../Crop.h"

namespace flipAxis{

   int flipMatric[2][2][2] = {
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


       int reflectedX = flipMatric[1][0][0] * pointCoordinates[0] + flipMatric[1][0][1] * pointCoordinates[1];
       int reflectedY = flipMatric[1][1][0] * pointCoordinates[0] + flipMatric[1][1][1] * pointCoordinates[1];

     
       myCrop::crop(reflectedX, reflectedY, orignalWidth - 1, 0);

       orignalX = reflectedX;
       orignalY = reflectedY;
   }

  
   void flipVertically(int &orignalX, int &orignalY, int orignalHeight){
       int pointCoordinates[2] = {orignalX, orignalY};

     
       int reflectedX = flipMatric[0][0][0] * pointCoordinates[0] + flipMatric[0][0][1] * pointCoordinates[1];
       int reflectedY = flipMatric[0][1][0] * pointCoordinates[0] + flipMatric[0][1][1] * pointCoordinates[1];


       myCrop::crop(reflectedX, reflectedY, 0, orignalHeight - 1);

       orignalX = reflectedX;
       orignalY = reflectedY;
   }
}
