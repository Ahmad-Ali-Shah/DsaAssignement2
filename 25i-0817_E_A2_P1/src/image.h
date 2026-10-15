#pragma once

//////////////////////////


//Image vector



/////////////////////////////


struct Pixel {
    unsigned int r;
    unsigned int g;
    unsigned int b;

    Pixel() : r(0), g(0), b(0) {}
    Pixel(unsigned int redVal, unsigned int greenVal, unsigned int blueVal) : r(redVal), g(greenVal), b(blueVal) {}

    bool operator==(const Pixel& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Pixel& other) const {
        return !(*this == other);
    }
};

struct Point {
    int coordinatesX;
    int coordinatesY;
};
