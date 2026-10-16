#pragma once
#include <iostream>
#include <string>
#include "../stack.h"
#include "command.h"

using namespace std;

class HistoryManager {

private:

    stackType<Command> undoStack;

    stackType<Command> redoStack;

    int pushCount;

    int popCount;


    Pixel** cloneGrid(Pixel** src, int w, int h) {

        if (!src || w <= 0 || h <= 0) 
        return nullptr;

        Pixel** copy = new Pixel*[h];

        for (int y = 0; y < h; y++) {

            copy[y] = new Pixel[w];

            for (int x = 0; x < w; x++) {

                copy[y][x] = src[y][x];

            }

        }

        return copy;

    }

    void freeGrid(Pixel** grid, int h) {

        if (!grid || h <= 0) 
        return;

        for (int y = 0; y < h; y++) {

            delete[] grid[y];

        }

        delete[] grid;

    }

public:

    HistoryManager(int maxCapacity = 50) : undoStack(maxCapacity), redoStack(maxCapacity), pushCount(0), popCount(0) {}

    void recordAction(const std::string& opName, Pixel** beforeImg, int w, int h) {

        Command cmd(opName, beforeImg, w, h);// SAVE COMMAND

        undoStack.push(cmd);

        pushCount++;


        // FOR THE REDO STACK TAKE , POP , INCREMEMENT POP COUNT AND FREE THE LINK

        while (!redoStack.isEmptyStack()) {

            Command popedCommand = redoStack.top();

            redoStack.pop();

            popCount++;

            popedCommand.freeSnapshot();

        }
    }

    bool undo(Pixel**& currentImg, int& currentW, int& currentH) {

        if (undoStack.isEmptyStack()) {

            return false;

        }


        Command lastCmd = undoStack.top();

        undoStack.pop();

        popCount++;


        Command redoCmd(lastCmd.opName, currentImg, currentW, currentH);

        redoStack.push(redoCmd);

        pushCount++;


        freeGrid(currentImg, currentH);

        currentImg = cloneGrid(lastCmd.previousImage, lastCmd.prevWidth, lastCmd.prevHeight);

        currentW = lastCmd.prevWidth;

        currentH = lastCmd.prevHeight;


        lastCmd.freeSnapshot();

        return true;

    }

    bool redo(Pixel**& currentImg, int& currentW, int& currentH) {

        if (redoStack.isEmptyStack()) {

            return false;

        }

        Command redoCmd = redoStack.top();

        redoStack.pop();

        popCount++;


        Command undoCmd(redoCmd.opName, currentImg, currentW, currentH);

        undoStack.push(undoCmd);

        pushCount++;

        freeGrid(currentImg, currentH);

        currentImg = cloneGrid(redoCmd.previousImage, redoCmd.prevWidth, redoCmd.prevHeight);

        currentW = redoCmd.prevWidth;

        currentH = redoCmd.prevHeight;


        redoCmd.freeSnapshot();

        return true;

    }

    bool canUndo() const {
         return !undoStack.isEmptyStack(); 
        }
    bool canRedo() const {
         return !redoStack.isEmptyStack(); 
        }
    int getUndoSize() const {
         return undoStack.size();
         }
    int getRedoSize() const { 
        return redoStack.size();
     }
    int getPushCount() const {
         return pushCount;
         }
    int getPopCount() const { 
        return popCount; 
    }

    std::string getUndoTopName() const {
        if (undoStack.isEmptyStack()) 
        return "None";

        return undoStack.top().opName;

    }

    std::string getRedoTopName() const {

        if (redoStack.isEmptyStack())
         return "None";
        return redoStack.top().opName;
    }

    void printUndoContents() const {

        if (undoStack.isEmptyStack()) {

            cout << "[Empty]\n";

            return;

        }

        for (int i = undoStack.size() - 1; i >= 0; i--) {

            cout << undoStack.getAt(i).opName << " ";

        }

        cout << "\n";

    }

    void printRedoContents() const {

        if (redoStack.isEmptyStack()) {

            cout << "[Empty]\n";

            return;

        }

        for (int i = redoStack.size() - 1; i >= 0; i--) {

            cout << redoStack.getAt(i).opName << " ";

        }

        cout << "\n";
        
    }
};
