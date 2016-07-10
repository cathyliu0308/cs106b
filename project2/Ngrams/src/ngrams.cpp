// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

int main() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;

    string file = getLine("Input file name? ");
    int numN = getInteger("Value of N?");
    int numWord;
    for (int i = 0; i < numN; i++) {
        numWord = getLine("# of random words to generate (0 to quit)? ");
        if (numWord == 0)
            break;
        else {
            genWords(file,numWord);
        }
    }


    cout << "Exiting." << endl;
    return 0;
}

Vector<string> genWords(string file, int numWord){
    Map<vector,vector> map;
    Vector<string> window;
}
