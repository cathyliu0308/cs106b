// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include "Maze.h"
#include "grid.h"


bool escapeMaze(Maze& maze, int row, int col) {
    if (!maze.inBounds(row,col)) {
        throw ("error!");
    } else {
/*
        Grid[int] pos(4,2);
        pos[0][0] = row + 1;
        pos[0][1] = col;
        pos[1][0] = row - 1;
        pos[1][1] = col;
        pos[2][0] = row;
        pos[2][1] = col + 1;
        pos[3][0] = row;
        pos[3][1] = col - 1;
*/
        int pos[4][2] = {{row+1,col},{row-1,col},{row,col+1},{row,col-1}};
        for (int i = 0; i < 4; i++) {
            if (maze.inBounds(pos[i][0],pos[i][1]) && maze.isOpen(pos[i][0],pos[i][1])) {
                maze.mark(pos[i][0],pos[i][1]);
                if (escapeMaze(maze, pos[i][0], pos[i][1])) {
                    return true;
                }
                maze.unmark(pos[i][0],pos[i][1]);
            } else if (! maze.inBounds(pos[i][0],pos[i][1])) {
                return true;
            }
        }
        return false;
    }
}
