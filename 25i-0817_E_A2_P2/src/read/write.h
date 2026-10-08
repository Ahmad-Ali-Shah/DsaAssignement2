#pragma once // Preprocessor directive to ensure this header is included only once per compilation unit
#include <fstream> // Standard library header for file stream input and output operations
#include <iostream> // Standard library header for console output and diagnostic messages
#include <string> // Standard library header for std::string representation of file paths
#include "../image.h" // Header containing custom Pixel and Point structure definitions

using namespace std; // Using standard namespace so standard library types can be used without std:: prefix

namespace ReadPath { // Namespace encapsulating all image loading, saving, and memory management routines

    // Inline function to export or save a 2D Pixel** image array to disk in binary format
    inline bool Write(std::string OutputPath, Pixel** img, int width, int height, bool asPPM = true) { // Export function

        // Open output file stream in binary mode for writing raw byte data
        fstream output(OutputPath.c_str(), ios::out | ios::binary); // Initialize binary output stream

        // Verify that the output file stream was successfully created
        if (!output.is_open()) { // Check if stream failed to open for writing
            cout << "[Error] Could not create file: " << OutputPath << "\n"; // Output diagnostic error message
            return false; // Return false indicating file export failure
        } // End of file open check

        // Check if caller requested writing a standard PPM P6 header
        if (asPPM) { // If asPPM flag is true, write header so image viewers can render it
            output << "P6\n" << width << " " << height << "\n255\n"; // Write ASCII P6 header with dimensions
        } // End of PPM header condition

        // Nested loops to serialize each Pixel's RGB components into binary bytes
        for (int y = 0; y < height; y++) { // Outer loop iterating through each row (height)
            for (int x = 0; x < width; x++) { // Inner loop iterating through each column (width)
                unsigned char rgb[3]; // Local byte array to store serialized RGB values
                rgb[0] = static_cast<unsigned char>(img[y][x].r); // Cast red unsigned int to byte
                rgb[1] = static_cast<unsigned char>(img[y][x].g); // Cast green unsigned int to byte
                rgb[2] = static_cast<unsigned char>(img[y][x].b); // Cast blue unsigned int to byte
                output.write(reinterpret_cast<const char*>(rgb), 3); // Write 3 bytes to the binary stream
            } // End of column serialization loop
        } // End of row serialization loop

        // Close the output file stream to ensure all buffered data is written to disk
        output.close(); // Flush and close binary output stream

        // Return true indicating successful file save/export
        return true; // Return true indicating successful write
    } // End of Write function

} // End of namespace ReadPath
