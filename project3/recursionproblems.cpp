// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
#include <math.h>
#include <strlib.h>
#include "filelib.h"
using namespace std;

int countKarelPaths(int street, int avenue) {
    if (street < 1 || avenue < 1) {
        throw ("illegal street or avenue!");
    }
    else if ((street == 1) && (avenue == 1)) {
        return 0;
    }
    else if ((street == 1) && (avenue > 1)) {
        return 1;
    }
    else if ((street > 1) && (avenue == 1)) {
        return 1;
    }
    else {
        return countKarelPaths(street - 1,avenue) + countKarelPaths(street,avenue - 1);
    }
}


int convertStringToInteger(string exp) {
    if (exp[0] == '-'){
        return -convertStringToInteger(exp.substr(1,exp.length()-1));
    }
    else {
        if (exp == "") {
            return 0;
        }
        else {
            char last = exp[exp.length()-1];
            if ((last - '0') > 9 || (last - '0') < 0)
                throw ("illegal string!");
            return convertStringToInteger(exp.substr(0,exp.length()-1)) * 10 + (last - '0');
        }
    }
}

bool isBalanced(string exp) {
    if (exp == "") {
        return true;
    }
    else {
        for (int i = 0; i < exp.length()-1; i ++) {
            //cout << "*" << level << endl;
            //cout << i << endl;
            if ((exp[i] == '[' && exp[i+1] == ']') || (exp[i] == '{' && exp[i+1] == '}') || (exp[i] == '(' && exp[i+1] == ')') || (exp[i] == '<' && exp[i+1] == '>')) {
                exp = exp.substr(0,i) + exp.substr(i+2);
                return isBalanced(exp);
                //flag = 1;
                //break;
            }
        }
        return false;
    }
}

double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    if (row < 0 || col < 0) {
        return 0.0;
    } else if (row == 0 && col == 0) {
        return weights[0][0];
    } else if (row >= 1 && col == 0) {
        return weightOnKnees (row - 1, col, weights)/2 + weights[row][col];
    } else if (row >= 1 && col == row) {
        return weightOnKnees (row - 1, row - 1, weights)/2 + weights[row][col];
    } else {
        return weightOnKnees (row - 1, col - 1, weights)/2 + weightOnKnees (row - 1, col, weights)/2 + weights[row][col];
    }
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if (x < 0 || y < 0 || size < 0 || order < 0) {
        throw ("Error");
    } else if (order == 0) {
        return;
    } else if (order == 1){
        gw.drawLine(x,y,x + size,y);
        gw.drawLine(x,y,x + size / 2,y+ sqrt(3) / 2 * size);
        gw.drawLine(x+size,y,x+size / 2,y+ sqrt(3) / 2 * size);
    } else {
        // left triangle
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        // right triangle
        drawSierpinskiTriangle(gw, x + size / 2, y, size / 2, order - 1);
        // bottom triangle
        drawSierpinskiTriangle(gw, x + size / 4, y + sqrt(3) / 4 * size,
                                   size / 2, order - 1);
    }

}

int floodFill(GBufferedImage& image, int x, int y, int color) {
    if ( x < 0 || y < 0 || x >= image.getWidth() || y >= image.getHeight())
    {
        throw ("Error!");
    }
    int curColor = image.getRGB(x,y);
    int res = fillHelper(image, x ,y, curColor, color);
    return res;
}
int fillHelper (GBufferedImage& image, int x, int y, int curColor, int newColor) {
    cout << x << "*" << y << "*" << image.getRGB(x,y) << "*" << curColor << "*" << newColor << endl;
    if ( x < 0 || y < 0 || x >= image.getWidth() || y >= image.getHeight())
    {
        return 0;
    }
    else if (image.getRGB(x,y) != curColor){
        return 0;
    }
    else
    {
        if (image.getRGB(x,y) != newColor)
        {
            image.setRGB(x,y,newColor);
            return fillHelper(image, x + 1, y, curColor, newColor) + fillHelper(image, x - 1, y, curColor, newColor) + fillHelper(image, x, y + 1, curColor, newColor) + fillHelper(image, x, y - 1, curColor, newColor) + 1;
        }
        else {
            return 0;
        }
    }
}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    Vector<string> v;
    HashMap<string,Vector<string>> lexicon;
    //ifstream input;
    //input.open(filename);
    string line;
    while (getline(input, line)) {
        Vector<string> curLine = stringSplit(line, "::=");
        Vector<string> rule = stringSplit(curLine[1],"|");
        lexicon.put(curLine[0].substr(1,curLine[0].size()-2), rule);
    }
    cout << lexicon << endl;
    return grammarGenerateHelper(lexicon, v, symbol, times));

}

Vector<string> grammarGenerateHelper(HashMap<string,Vector<string>> lexicon, Vector<string> res, string symbol, int times)) {

    int flag = 0;
    if (!lexicon.containsKey(symbol)) {
        return;
    } else if (times == 0) {
        return;
    } else {
        for (string name : lexicon[symbol]) {
            for (int i = 0; i < )
            if (name == symbol) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            Vector<string> words = lexicon[symbol];
            int lens = words.size();
            int index = randomInteger(0,words.size()-1);
            res.add(words[index]);
            grammarGenerateHelper(lexicon, symbol, times-1);
        } else {
            return grammarGenerateHelper(lexicon, name, times);
        }
    }
    return res;
}
