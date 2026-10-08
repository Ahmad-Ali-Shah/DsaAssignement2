#pragma once

// Representation of a single color pixel in the RGB cube
struct Pixel {
    unsigned int r;
    unsigned int g;
    unsigned int b;

    bool operator==(const Pixel& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Pixel& other) const {
        return !(*this == other);
    }
};

// Image alias representing a pixel cell
using Image = Pixel;
