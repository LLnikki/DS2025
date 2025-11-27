#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "HuffTree.h"
using namespace std;
int main() {
    int freq[26] = {0};
    ifstream fin("speech.txt");
    if (!fin) {
        cerr << "Cannot open speech.txt" << endl;
        return 1;
    }
    char ch;
    while (fin.get(ch)) {
        if (isalpha(ch)) {
            freq[tolower(ch) - 'a']++;
        }
    }
    fin.close();
    HuffTree<HuffChar> huffTree;
    huffTree.build(freq);
    cout << "Huffman Code Table:" << endl;
    huffTree.printCodeTable();
    cout << "Encoding examples:" << endl;
    string words[] = {"dream", "freedom", "justice", "brotherhood"};
    for (int i = 0; i < 4; i++) {
        string encoded = huffTree.encodeString(words[i]);
        cout << words[i] << " -> " << encoded << endl;
    }
    return 0;
}
