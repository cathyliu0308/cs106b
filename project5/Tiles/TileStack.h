// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _tilestack_h
#define _tilestack_h

#include <iostream>
#include <string>
#include "gobjects.h"
#include "gwindow.h"
#include "TileNode.h"
#include "TileStack.h"
using namespace std;

class TileStack {
public:
    TileStack();
    ~TileStack();
    void pushTile(int x, int y, int width, int height, string color);
    void drawAll(GWindow& window) const;
    void highlight(int x, int y);
    void raise(int x, int y);
    void remove(int x, int y);
    void clear();

private:
    TileNode* front;
};

#endif
