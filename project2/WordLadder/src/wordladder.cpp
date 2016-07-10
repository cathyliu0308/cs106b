// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "filelib.h"
#include "simpio.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
using namespace std;

Stack<string> wordLadder(string w1, string w2, Lexicon dict);
bool isContain(Stack<string> path, string w);
bool isNeighbor(string w1,string w2);

int main() {
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;


    string file;
    Lexicon dict;
    while(true)
    {
        file = getLine("Dictionary file name? ");
        if (fileExists(file) == false)
        {
            cout << "Unable to open that file. Try again." << endl;
        }
        else
        {           
            dict.addWordsFromFile(file);
            break;
            /*
            ifstream input;
            input.open(file);
            string line;
            getline(input, line);
            int row = stringToInteger(line);
            getline(input, line);
            */
        }
    }
    while (true){
        string word1 = getLine("Word #1 (or Enter to quit):");
        string word2 = getLine("Word #1 (or Enter to quit):");
        if (! dict.contains(word1) || dict.contains(word2))
            cout << "The two words must be found in the dictionary." << endl;
        else if (word1 == "\n" || word2 == "\n")
            break;
        else
        {
            if (word1 == word2)
                cout << "The two words must be different." << endl;
            else if (word1.length() != word2.length())
                cout << "The two words must be the same length." << endl;
            else
            {
                Stack<string> ladder;
                ladder = wordLadder(word1,word2,dict);
                cout << ladder << endl;
            }
        }
    }

    cout << "Have a nice day." << endl;
    return 0;
}

Stack<string> wordLadder(string w1, string w2, Lexicon dict)
{
    Stack<string> s;
    Queue<string> q;
    s.push(w1);
    q.enqueue(s);
    Stack<string> path;
    Stack<string> res;
    int minlens = dict.size()+1;
    string word;
    string neighbor;
    Set<char> alphabet {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while (!q.isEmpty())
    {
        path = q.dequeue();
        word = path.peek();
        for (char c::alphabet)
        {
            for (int i = 0; i < word.length(); i++)
            {
                neighbor += word.substr(0,i);
                neighbor += c;
                neighbor += word.substr(i+1,word.length()-1-i);
                if ((neighbor != word) && (dict.contains(neighbor)) && (! isContain(path,neighbor)))
                {
                    if (neighbor == w2)
                    {
                        if (path.size() < minlens)
                        {
                            minlens = path.size();
                            res = path;
                        }
                    }
                    else
                    {
                        Stack<string> tmp = path;
                        tmp.push(neighbor);
                        q.enqueue(tmp);
                    }
                }
            }
        }
    }
    return res;
}

bool isNeighbor(string w1,string w2)
{
    //Set<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int cnt = 0;
    if ((w1 == w2) || (w1.length() != w2.length()))
        return false;
    else {
        for (int i = 0; i < w1.length(); i++){
            if (w1[i] != w2[i])
                cnt ++;
            if (cnt > 1)
                return false;
            else
                continue;
        }
        return true;
    }

}

bool isContain(Stack<string> path, string w)
{
    string s;
    while (!path.isEmpty()) {
        s = path.pop();
        if (s == w)
            return true;
    }
    return false;
}
