// Please feel free to add any other #includes you need!
#include <string>
#include "boggle.h"
#include "grid.h"
#include "lexicon.h"
#include "strlib.h"
#include <sstream>
#include <string>
using namespace std;

bool humanHelper(Grid<char>& board, Grid<int>& visited, string word, string chosen, int i, int j);
Set<string> computerHelper(Grid<char>& board, Grid<int>& visited, Lexicon& dictionary, string chosen, int i, int j, Set<string>& allWords);

bool humanWordSearch(Grid<char>& board, string word) {
    if (word.length() < MIN_WORD_LENGTH) {
        return false;
    } else {
        string chosen = "";
        word = toUpperCase(word);
        Grid<int> visited(BOARD_SIZE, BOARD_SIZE);
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                visited[i][j] = 0;
            }
        }
        //cout << visited << endl;
        //int visited[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 4; j ++) {
                if (board[i][j] == word[0]) {
                    visited[i][j] = 1;
                    chosen += word[0];
                    word = word.substr(1);
                    if (humanHelper(board,visited,word,chosen,i,j)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

bool humanHelper(Grid<char>& board, Grid<int>& visited, string word, string chosen, int i, int j) {
    if (word.size() == 0) {
        return true;
    } else {
        int pos[8][2] = {{i-1,j-1},{i-1,j},{i-1,j+1},{i,j-1},{i,j+1},{i+1,j-1},{i+1,j},{i+1,j+1}};
        for (int k = 0; k < 8; k++) {
            if ((pos[k][0] >=0 && pos[k][0] <4) && (pos[k][1] >=0 && pos[k][1] < 4) && (visited[pos[k][0]][pos[k][1]] == 0) && (board[pos[k][0]][pos[k][1]] == word[0])) {
                chosen += word[0];
                word = word.substr(1);
                visited[pos[k][0]][pos[k][1]] = 1;
                if (humanHelper(board,visited,word,chosen,pos[k][0],pos[k][1])) {
                    return true;
                }
                stringstream ss;
                string s;
                char c = chosen[chosen.size()-1];
                ss << c;
                ss >> s;
                word.insert(0,s);
                chosen = chosen.substr(0,chosen.size() - 1);
                visited[pos[k][0]][pos[k][1]] = 0;
            }
        }
        return false;
    }
}



Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary) {
    Set<string> allWords;
    //return allWords;
    if (dictionary.size() == 0) {
        return allWords;
    } else {
        Grid<int> visited(BOARD_SIZE, BOARD_SIZE);

        //for (string word : dictionary) {
       //     word = toUpperCase(word);
        //}
        //cout << dictionary << endl;
        //if (word.size() >= MIN_WORD_LENGTH) {
            //word = toUpperCase(word);
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 4; j ++) {
                string chosen = "";
                char c = board[i][j];
                string s = string("") + c;
                //cout << s << endl;
                s = toLowerCase(s);
                if (dictionary.containsPrefix(s)) {
                    //cout << s << endl;
                    for (int i = 0; i < BOARD_SIZE; i++) {
                        for (int j = 0; j < BOARD_SIZE; j++) {
                            visited[i][j] = 0;
                        }
                    }
                    visited[i][j] = 1;
                    chosen += board[i][j];
                    //cout << chosen << endl;
                    computerHelper(board,visited,dictionary,chosen,i,j,allWords);
                }
            }
        }
        return allWords;
    }
}

/*
string computerHelper(Grid<char>& board, Grid<int>& visited, Lexicon& dictionary, string chosen, int i, int j,string word) {
    if (word == chosen) {
        return chosen;
    } else {
        int pos[8][2] = {{i-1,j-1},{i-1,j},{i-1,j+1},{i,j-1},{i,j+1},{i+1,j-1},{i+1,j},{i+1,j+1}};
        for (int k = 0; k < 8; k++) {
            if ((pos[k][0] >=0 && pos[k][0] <4) && (pos[k][1] >=0 && pos[k][1] < 4)) {
                string tmp = chosen + board[pos[k][0]][pos[k][1]];
                if ((visited[pos[k][0]][pos[k][1]] == 0) && (dictionary.containsPrefix(tmp)))
                {
                    chosen += board[pos[k][0]][pos[k][1]];
                    visited[pos[k][0]][pos[k][1]] = 1;
                    if (computerHelper(board,visited,dictionary,chosen,pos[k][0],pos[k][1],word) == word)
                        return chosen;
                    chosen = chosen.substr(0,chosen.size() - 1);
                    visited[pos[k][0]][pos[k][1]] = 0;
                }
            }
        }
    }
    return "";
}
*/

Set<string> computerHelper(Grid<char>& board, Grid<int>& visited, Lexicon& dictionary, string chosen, int i, int j,Set<string>& allWords) {
    chosen = toLowerCase(chosen);
    //cout << chosen << "   " << "i=" << i << "   " << "j=" << j << endl;
    //if (dictionary.contains(chosen) && chosen.size() >= 4) {
    //    cout << "great!! the chosen = " << chosen << endl;
    //    allWords.add(chosen);
    //    cout << allWords << endl;
    //} else {
        int pos[8][2] = {{i-1,j-1},{i-1,j},{i-1,j+1},{i,j-1},{i,j+1},{i+1,j-1},{i+1,j},{i+1,j+1}};
        for (int k = 0; k < 8; k++) {
            if ((pos[k][0] >=0 && pos[k][0] <4) && (pos[k][1] >=0 && pos[k][1] < 4)) {
                if (dictionary.contains(chosen) && chosen.size() >= 4) {
                        //cout << "great!! the chosen = " << chosen << endl;
                    chosen = toUpperCase(chosen);
                    allWords.add(chosen);
                        //cout << allWords << endl;
                }
                string tmp = chosen + board[pos[k][0]][pos[k][1]];
                tmp = toLowerCase(tmp);
                //cout << tmp << endl;
                if ((visited[pos[k][0]][pos[k][1]] == 0) && (dictionary.containsPrefix(tmp))) {
                    //cout << "***" << tmp << endl;
                    chosen += board[pos[k][0]][pos[k][1]];
                    //word = word.substr(1);
                    visited[pos[k][0]][pos[k][1]] = 1;
                    computerHelper(board,visited,dictionary,chosen,pos[k][0],pos[k][1],allWords);

                    //stringstream ss;
                    //string s;
                    //char c = chosen[chosen.size()-1];
                    //ss << c;
                    //ss >> s;
                    //s += c;
                    //word.insert(0,s);
                    chosen = chosen.substr(0,chosen.size() - 1);
                    visited[pos[k][0]][pos[k][1]] = 0;
                }
            }
        }
    //}
    return allWords;
}
