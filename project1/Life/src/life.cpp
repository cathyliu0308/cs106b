// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include <cstring>
using namespace std;

int checkNeighbor(int x, int y, int row, int col, char** map);
bool isValid(int i,int j,int row,int col);
void generate (char** map, int row, int col);

int main()
{
    cout << "Welcome to the CS 106B Game of Life, " << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;

    while(true)
    {
        string file = getLine("Grid input file name? ");
        if (fileExists(file) == false)
        {
            cout << "Unable to open that file. Try again." << endl;
        }
        else
        {
            ifstream input;
            input.open(file);
            string line;
            getline(input, line);
            int row = stringToInteger(line);
            getline(input, line);
            int col = stringToInteger(line);
            //char map[row][col];
            char** map= new char*[row];
            for (int i=0;i<row;i++)
                map[i]=new char[col];
            for (int i = 0; i < row; i++){
                getline(input,line);
                strcpy(map[i],line.c_str());

                //for (int j = 0; j < col; j++)
               //     cout << map[i][j] << endl;
                cout << map[i] << endl;
            }

       //     cout << row << col << endl;
       /*     while (getline(input, line))
            {
                if (line[0]== "X") || (line[0] == "-"){
                    cout << line << endl;
                }
            }
       */
            while (true){
                string choice = getLine("a)nimate, t)ick, q)uit? ");
                if (choice == "q")
                {
                    break;
                }
                else if (choice == "a")
                {
                    /*
                    int frame;
                    while (true)
                    {
                        frame = getInteger("How many frames?");
                        if (frame < 0)
                        {
                            //cout << "Illegal integer format. Try again." << endl;
                        }
                        else
                        {
                            break;
                        }
                    }
                    */
                    //int frame = 0;
                    //while (frame <= 0)
                    int frame = getInteger("How many frames?");
                    for (int i = 0; i< frame; i++){
                        //colony.generation(map,row,col);
                        //cout << "***" << endl;
                        pause(50);
                        clearConsole();
                        generate(map, row, col);

                    }

                }

                else if (choice == "t")
                    //cout << "t" << endl;
                    //colony.generation(map,row,col);
                    //cout << "***" << endl;
                    generate(map, row, col);
                else {
                    cout << "Illegal integer format. Try again." << endl;
                }
                input.close();
            }
            break;
        }



    }

    cout << "Have a nice Life!" << endl;
    return 0;
}
/*
class Colony
{
    void generation (string, int, int);
};
void Colony::generation (string map,int row,int col){
    cout << "***" << endl;

}
*/


void generate (char** map, int row, int col)
{
    int cnt;
    int** change= new int*[row];
    for (int i=0;i<row;i++)
        change[i]=new int[col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cnt = checkNeighbor(i,j,row,col,map);
            if (((cnt == 2) && (map[i][j] == 'X')) || (cnt == 3))
            {
                change[i][j] = 'X';
            }

        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (change[i][j] == 'X')
            {
                map[i][j] = 'X';
            }
            else
            {
                map[i][j] = '-';
            }

        }
        cout << map[i] << endl;
    }
    delete [] change;

}

bool isValid(int i,int j,int row,int col)
{
    if (i>=0 && i<row && j>=0 && j<col)
        return true;
    else
        return false;
}

int checkNeighbor(int x, int y, int row, int col, char** map)
{
    int cnt=0;
    int deltaX[8] = {-1,-1,-1,1,1,1,0,0};
    int deltaY[8] = {0,1,-1,0,1,-1,1,-1};
    for (int i = 0; i < 8; i++)
    {
        int x1 = x+deltaX[i];
        int y1 = y+deltaY[i];
        if ((isValid(x1, y1, row, col) == true) && (map[x1][y1] == 'X'))
              cnt ++;
    }
    return cnt;
}
