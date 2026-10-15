#pragma once
#include "../image.h"

struct HistoryGridHelper {
    static Pixel** cloneGrid(Pixel** src, int w, int h) {
        if (!src || w <= 0 || h <= 0) return nullptr;
        Pixel** copy = new Pixel*[h];
        for (int y = 0; y < h; y++) {
            copy[y] = new Pixel[w];
            for (int x = 0; x < w; x++) {
                copy[y][x] = src[y][x];
            }
        }
        return copy;
    }

    static void freeGrid(Pixel** grid, int h) {
        if (!grid || h <= 0) return;
        for (int y = 0; y < h; y++) {
            delete[] grid[y];
        }
        delete[] grid;
    }
};
