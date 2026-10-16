#pragma once
#include "historyRecord.h"

struct HistoryCoalescing {


    static void mergeClippedPixels(HistoryRecord& topRec, const ClippedPixel* currentClipped, int tempCount) {

        for (int i = 0; i < tempCount; i++) {

            bool alreadyTracked = false;

            for (int j = 0; j < topRec.clippedCount; j++) {
                
                if (topRec.clippedPixels[j].x == currentClipped[i].x && topRec.clippedPixels[j].y == currentClipped[i].y) {

                    alreadyTracked = true;

                    break;

                }

            }

            if (!alreadyTracked) {

                topRec.addClippedPixel(currentClipped[i]);

            }
        }

    }
    
};
