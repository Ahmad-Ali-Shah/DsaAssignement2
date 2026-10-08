#pragma once

//////////////////////////


//Image vector



/////////////////////////////


struct Pixel {
    unsigned int r;
    unsigned int g;
    unsigned int b;

    Pixel() : r(0), g(0), b(0) {}
    Pixel(unsigned int _r, unsigned int _g, unsigned int _b) : r(_r), g(_g), b(_b) {}

    bool operator==(const Pixel& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Pixel& other) const {
        return !(*this == other);
    }
};




