#pragma once
#include "../../image.h"
#include "../../circularQueue.h"

/////////////////////////////////////////

// Coordinates queue for breadth-first traversal

//////////////////////////////////////////



namespace MybucketFill{

    void ReplaceNearOneQueue(Pixel** InputImage , double width , double height  , int startxCoor , int startyCoor,  unsigned int newR, unsigned int newG, unsigned int newB ){

        int w = static_cast<int>(width);

        int h = static_cast<int>(height);

        if (w <= 0 || h <= 0) {

            return;

        }

        if (startxCoor < 0 || startxCoor >= w || startyCoor < 0 || startyCoor >= h) {

            return;

        }


        Pixel targetColor = InputImage[startyCoor][startxCoor];

        Pixel replacementColor = {newR, newG, newB};


        
        if (targetColor == replacementColor) {

            return;

        }

        
        int queueCapacity = (w * h * 4 > 100) ? (w * h * 4) : 100;

        queueType<Point> StoringBucket(queueCapacity);


        
        StoringBucket.addQueue({startxCoor, startyCoor}); 


        while(!StoringBucket.isEmptyQueue()){
            
            Point currentPoint = StoringBucket.front();

            int valX = currentPoint.coordinatesX;

            int valY = currentPoint.coordinatesY;


            StoringBucket.deleteQueue();


            if (InputImage[valY][valX] != targetColor) {

                continue;
                
            }

            InputImage[valY][valX] = replacementColor;

            int dx[4] = {0, 0, -1, 1}; //up down left right
            int dy[4] = {-1, 1, 0, 0};

            for(int i=0 ; i<4 ; i++){

                int nx = valX + dx[i];
                int ny = valY + dy[i];

                if(nx >= 0 && nx < w && ny >= 0 && ny < h){

                    if (InputImage[ny][nx] == targetColor) {
                        StoringBucket.addQueue({nx , ny});
                    }
                }
            }
        }
    }
}