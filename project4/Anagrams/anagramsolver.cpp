// Please feel free to add any other #includes you need!
#include <iostream>
#include <string>
#include "letterinventory.h"
#include "set.h"
#include "strlib.h"
using namespace std;

int helper (Vector<Vector<string>>& res, LetterInventory& letters, Vector<string>& chosen, Set<string>& dictionary, int max);
int findAnagrams(string phrase, int max, Set<string>& dictionary) {
    LetterInventory letters;
    letters = LetterInventory(phrase);
    Vector<string> chosen;
    Vector<Vector<string>> res;
    if (max < 0) {
        throw ("Error!");
    }
    return helper(res,letters,chosen,dictionary,max);
}

int helper (Vector<Vector<string>>& res, LetterInventory& letters, Vector<string>& chosen, Set<string>& dictionary, int max) {
    //cout << dictionary << endl;
   // cout << letters << endl;
    if (max >= 0 && letters.size() == 0) {
        res.add(chosen);
        cout << chosen << endl;
        //return res;
    }
    else {
        for (string s : dictionary) {
            if (letters.contains(s)){
                chosen.add(s);
                //dictionary.remove(s);
                letters.subtract(s);
                helper(res,letters,chosen,dictionary,max - 1);
                chosen.remove(chosen.size() - 1);
                //dictionary.add(s);
                letters.add(s);
            }
        }
    }
    return res.size();
}
