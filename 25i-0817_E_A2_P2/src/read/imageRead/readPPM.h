#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../../image.h"

namespace ReadPath {

    Pixel** readPPM(const std::string& path, int& width, int& height) {

        if (path.empty()) {

            return nullptr;

        }

        std::ifstream file(path.c_str(), std::ios::binary); // OPEN FILE AND READ FILE BY FILE 

        if (!file.is_open()) {

            return nullptr;

        }


        std::string magic;

        file >> magic;

        if (magic != "P6") {

            file.close();// NOT PPM 

            return nullptr;

        }

        int maxVal = 255;

        file >> width >> height >> maxVal;

        file.get();


        if (width <= 0 || height <= 0 || maxVal <= 0) {
            file.close(); // NO IIMSGE 

            return nullptr;

        }

        Pixel** grid = new Pixel*[height];

        for (int r = 0; r < height; r++) {

            grid[r] = new Pixel[width];

        }

        for (int r = 0; r < height; r++) {

            for (int c = 0; c < width; c++) {

                unsigned char rgb[3];

                file.read(reinterpret_cast<char*>(rgb), 3);//READS THE 3 CONZEPTIVE VALU E FROM LEFT POINTEER 

                grid[r][c].r = static_cast<unsigned int>(rgb[0]);

                grid[r][c].g = static_cast<unsigned int>(rgb[1]);

                grid[r][c].b = static_cast<unsigned int>(rgb[2]);

            }
        }

        file.close();
        return grid;
    }

}
