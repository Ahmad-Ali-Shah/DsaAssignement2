#pragma once
#include <string>
#include "../image.h"

struct Command {

    std::string opName;

    Pixel** previousImage;

    int prevWidth;

    int prevHeight;


    Command() : opName(""), previousImage(nullptr), prevWidth(0), prevHeight(0) {}

    Command(const std::string& name, Pixel** img, int w, int h) : opName(name), prevWidth(w), prevHeight(h) {
        
        if (img && w > 0 && h > 0) {

            previousImage = new Pixel*[h];

            for (int y = 0; y < h; y++) {
                
                previousImage[y] = new Pixel[w];

                for (int x = 0; x < w; x++) {

                    previousImage[y][x] = img[y][x];


                }

            }

        } 
        else {

            previousImage = nullptr;

        }
    }
// DELETE THAT BOI
    void freeSnapshot() {

        if (previousImage && prevHeight > 0) {

            for (int y = 0; y < prevHeight; y++) {

                delete[] previousImage[y];

            }

            delete[] previousImage;

            previousImage = nullptr;

        }
    }
};
