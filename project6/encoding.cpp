#include "encoding.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "pqueue.h"
#include "filelib.h"
using namespace std;

Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    char key;
    while (input.get(key)) {
        //cout << input.get() << endl;
        //key = (int) input.get();
        if (freqTable.containsKey(key)) {
            freqTable[key] ++;
        } else {
            freqTable.add(key,1);
        }
    }
    freqTable.add(PSEUDO_EOF,1); // put EOF to the map;
    //cout << freqTable << endl;
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pq;
   // HuffmanNode* root = new HuffmanNode();
    for (int key : freqTable.keys()) {
        HuffmanNode* node = new HuffmanNode();
        node->character = key;
        node->count = freqTable[key];
        node->zero = NULL;
        node->one = NULL;
        pq.enqueue(node,node->count);

    }
    while (pq.size() > 1) {
        HuffmanNode* zero = pq.peek();
        pq.dequeue();
        HuffmanNode* one = pq.peek();
        pq.dequeue();
        HuffmanNode* parent = new HuffmanNode();
        parent->character = NOT_A_CHAR;
        parent->count = zero->count + one->count;
        parent->zero = zero;
        parent->one = one;
        pq.enqueue(parent,parent->count);
    }
    HuffmanNode* root = pq.peek();
    return root;

}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    string value = "";
    if (encodingTree == NULL)
        return encodingMap;
    return helper(encodingTree,encodingMap,value);
}

Map<int, string> helper(HuffmanNode* node,Map<int, string>& encodingMap,string value) {
    if (! node->isLeaf()) {
        helper(node->zero,encodingMap,value + "0");
        helper(node->one,encodingMap,value + "1");
    }
    else {
        encodingMap.add(node->character,value);
        return encodingMap;
    }
    return encodingMap;
}




void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    rewindStream(input);
    char key;
    while (input.get(key)) {
        string s = encodingMap.get(key);
        for (int i = 0; i < s.length(); i++)
            output.writeBit(s[i] - '0');
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int bit;
    HuffmanNode* node = encodingTree;
    while ((bit = input.readBit()) != -1) {
        if (bit == 0 && node->zero != NULL)
            node = node->zero;
        else if (bit == 1 && node->one != NULL)
            node = node->one;
        else if (bit == 0 && node->zero == NULL) {
            output.put(node->character);
            node = encodingTree->zero;
        } else {
            output.put(node->character);
            node = encodingTree->one;
        }
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable = buildFrequencyTable(input);
    output << freqTable;
    HuffmanNode* root = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(root);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* root = buildEncodingTree(freqTable);
    decodeData(input, root, output);
}

void freeTree(HuffmanNode* node) {
    if(node->isLeaf()){
        delete node;
        return;
    } else {
        freeTree(node->zero);
        freeTree(node->one);
    }
}
