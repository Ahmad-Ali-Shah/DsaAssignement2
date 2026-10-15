////////////////////////////

// same like that we shall implement the rotation classes

// i shall use the standered matrix for the rotation for a more prominent view

////////////////////////////////


#pragma once
#include <cmath> // for sine cosine and other functions 
#include "../../image.h"
#include "../crop.h"

namespace rotateObject{
    


    // HERE YOU NEED TO ROTATE AND THEN TRANSLATE IN THE RELEVENT AXIS IN ORDER TO MAKE THE HEIGHT AND WEIGTH CONSTANT

    void rotate(int &orignalX , int &orignalY , int orignalHeight , int orignalWidth , double AngleRotate){

        // converting to radian 

           const double PI = 3.14159265358979323846;

           double radians = AngleRotate * (PI / 180.0);

        // finding cosine and sin value so use that as below in the rotation matrix

           int cosVal = static_cast<int>(round(cos(radians)));

           int sinVal = static_cast<int>(round(sin(radians)));

     
           int rotationMatrix[1][3][3]{

            /*
              // x axis

              {
                  {1,0,0,},
                  { 0 , cos(AngleRotate) , -sin(AngleRotate)},
                  {0 , sin(AngleRotate) , cos(AngleRotate)}

              }
              



              // y axis

              {

                {cos(AngleRotate),0,sin(AngleRotate)},
                {0,1,0},
                {-sin(AngleRotate) , 0 , cos(AngleRotate)}
              },

 */
              // z axis


              {
               {cosVal , -sinVal , 0},
               {sinVal , cosVal , 0},
               {0,0,1}

              }




            



           };



           // since that's always for the xy rotation so we only treat for 0 i added other to make the generalized form but indexing is still 0


           // first rotate then traanslate the composite matrix
           

           int resultingCoordinates[3] = {orignalX , orignalY , 1};


           // Matrix multiplication in O(1) index form (its nothing but x = cosx - sinx  and y = cosx + sinx )


           int rotatedX = rotationMatrix[0][0][0] * resultingCoordinates[0] + rotationMatrix[0][0][1] * resultingCoordinates[1] + rotationMatrix[0][0][2] * resultingCoordinates[2];


           int rotatedY = rotationMatrix[0][1][0] * resultingCoordinates[0] + rotationMatrix[0][1][1] * resultingCoordinates[1] + rotationMatrix[0][1][2] * resultingCoordinates[2];




           // Determine translation shift to bring rotated image back into positive bounds

           int shiftX = 0;

           int shiftY = 0;


           int angleMod = (static_cast<int>(round(AngleRotate)) % 360); // for handling the coterminal angles 

           if (angleMod < 0) 
           
           angleMod += 360; 

           if (angleMod == 90) {

               shiftX = orignalHeight - 1;

               shiftY = 0; // handling the translation after rotations 


               // nothing but different quadrents here its in 2nd and 3rd and 4th in next ones 

           }
            else if (angleMod == 180) {

               shiftX = orignalWidth - 1;

               shiftY = orignalHeight - 1;


           } else if (angleMod == 270) {

               shiftX = 0;

               shiftY = orignalWidth - 1;


           }

           // Translate using our Crop translation matrix function

           myCrop::crop(rotatedX, rotatedY, shiftX, shiftY);


           orignalX = rotatedX;

           orignalY = rotatedY;

    }
}
