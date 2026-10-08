/*
idea:
Takes a colored RGB image and converts it into a 
classic black-and-white / monochrome photo.


converting RGB to Grayscale is an Inner Product (Dot Product)


In Linear Algebra, converting RGB to Grayscale is an Inner Product (Dot Product) of the 
3D color vector

with the Human Luminance Weight Vector



In the 1950s, television engineers had a massive engineering problem: 
Color TV was being invented, 
but millions of households 
still had Black & White TVs.


mathematical projection vector to convert 3-channel RGB 
into a single Black & White channel



The Global International Standards

There are two classical standereds of taking vectors 

1)ITU-R Recommendation BT.601 (1982) (old)

w = [0.299 , 0.587 , 0.114]t

2) The Modern HDTV Standar

When modern computer monitors and HDTVs 
replaced old CRT phosphors with sRGB primaries, 
the weights were updated slightly to


w = [0.2126 , 0.7152 , 0.0722]t

so we are using modern one we canalso use the old one tooo but as per standered 
its needed there
*/
#pragma once
#include <cmath>
#include "../../image.h"
namespace MygreyScale{

    void greyScale(double &R , double &G , double &B){

        // its wtc 

        double  Result = 0.2126*R+0.7152*G+0.0722*B;

        R = round(Result);
        G = round(Result);
        B = round(Result);
    }

    // Overload for unsigned int channels (matching brightness.h and image pixels)
    void greyScale(unsigned int &R , unsigned int &G , unsigned int &B){

        double Result = 0.2126 * static_cast<double>(R) + 0.7152 * static_cast<double>(G) + 0.0722 * static_cast<double>(B);

        unsigned int gray = static_cast<unsigned int>(round(Result));
        R = gray;
        G = gray;
        B = gray;
    }
}
