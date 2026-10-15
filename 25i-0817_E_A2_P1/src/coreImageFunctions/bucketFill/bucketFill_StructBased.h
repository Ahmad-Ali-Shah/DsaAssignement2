#pragma once
#include "../../image.h"
#include "../../stack.h"

/////////////////////////////////////////


// class point stack that are visited btw


//////////////////////////////////////////



namespace MybucketFill{

    inline void ReplaceNearOne(Pixel** InputImage , double width , double height  , int startxCoor , int startyCoor,  unsigned int newR, unsigned int newG, unsigned int newB ){

        int w = static_cast<int>(width);
        int h = static_cast<int>(height);

        if (w <= 0 || h <= 0) {
            return;
        }

        // Boundary check for starting coordinate
        if (startxCoor < 0 || startxCoor >= w || startyCoor < 0 || startyCoor >= h) {
            return;
        }

        Pixel targetColor = InputImage[startyCoor][startxCoor];
        Pixel replacementColor = {newR, newG, newB};

        // Guard against infinite loop if replacement equals target (Section 6.6)
        if (targetColor == replacementColor) {
            return;
        }

        stackType<Point> StoringBucket(w * h);

        StoringBucket.push({startxCoor,startyCoor}); //pushed the starting coordinates


        while(!StoringBucket.isEmptyStack()){
            // get the point 

            Point currentPoint = StoringBucket.top();
            int valX = currentPoint.coordinatesX;
            int valY = currentPoint.coordinatesY;

            StoringBucket.pop();

            // Skip if this pixel was already filled or does not match target color
            if (InputImage[valY][valX] != targetColor) {
                continue;
            }

            // first of all editPixel
            InputImage[valY][valX] = replacementColor;

            int dx[4] = {0, 0, -1, 1}; //up down left right
            int dy[4] = {-1, 1, 0, 0};

            for(int i=0 ; i<4 ; i++){

                int nx = valX + dx[i];
                int ny = valY + dy[i];

                if(nx >= 0 && nx < w && ny >= 0 && ny < h){// just correct that condition

                    if (InputImage[ny][nx] == targetColor) {
                        // push ts again
                        StoringBucket.push({nx , ny});
                    }
                }
            }
        }
        // replaced all lnked element 

        
    }
}