#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "BinTree.h"
#include "Bitmap.h"
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <string>
struct HuffChar {
    char ch;
    int weight;
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}
    bool operator<(const HuffChar& hc) const {
        return weight > hc.weight;
    }
};
template<typename T>
class HuffTree {
public:
    typedef std::map<char, char*> HuffCodeMap;
private:
    BinTree<HuffChar>* _tree;
    HuffCodeMap _codeMap;
    struct Cmp {
        bool operator()(BinTree<HuffChar>* a, BinTree<HuffChar>* b) {
            return a->root()->data.weight > b->root()->data.weight;
        }
    };
public:
    HuffTree() : _tree(NULL) {}
    ~HuffTree() { 
        if (_tree) delete _tree;
        for (typename HuffCodeMap::iterator it = _codeMap.begin(); it != _codeMap.end(); ++it) {
            delete[] it->second;
        }
    }
    void build(const int* freq) {
        std::priority_queue<BinTree<HuffChar>*, std::vector<BinTree<HuffChar>*>, Cmp> forest;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                HuffChar hc('a' + i, freq[i]);
                BinTree<HuffChar>* tree = new BinTree<HuffChar>;
                tree->insertAsRoot(hc);
                forest.push(tree);
            }
        }
        while (forest.size() > 1) {
            BinTree<HuffChar>* t1 = forest.top(); forest.pop();
            BinTree<HuffChar>* t2 = forest.top(); forest.pop();
            BinTree<HuffChar>* s = new BinTree<HuffChar>;
            s->insertAsRoot(HuffChar('^', t1->root()->data.weight + t2->root()->data.weight));
            s->root()->lc = t1->root();
            s->root()->rc = t2->root();
            t1->root()->parent = s->root();
            t2->root()->parent = s->root();
            forest.push(s);
        }
        if (!forest.empty()) {
            _tree = forest.top();
            generateCodes(_tree->root(), "");
        }
    }
    void generateCodes(BinNode<HuffChar>* v, const std::string& code) {
        if (!v->lc && !v->rc) {
            char* bits = new char[code.length() + 1];
            strcpy(bits, code.c_str());
            _codeMap[v->data.ch] = bits;
            return;
        }
        if (v->lc) {
            generateCodes(v->lc, code + "0");
        }
        if (v->rc) {
            generateCodes(v->rc, code + "1");
        }
    }
    char* encode(char ch) {
        if (_codeMap.find(ch) != _codeMap.end())
            return _codeMap[ch];
        return NULL;
    }
    std::string encodeString(const std::string& str) {
        std::string result;
        for (size_t i = 0; i < str.length(); i++) {
            char* code = encode(str[i]);
            if (code) result += code;
        }
        return result;
    }
    void printCodeTable() {
        for (typename HuffCodeMap::iterator it = _codeMap.begin(); it != _codeMap.end(); ++it) {
            if (it->first != '^') {
                std::cout << it->first << ": " << it->second << std::endl;
            }
        }
    }
};
#endif
