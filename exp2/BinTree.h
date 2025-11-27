#ifndef BINTREE_H
#define BINTREE_H
template<typename T>
struct BinNode {
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;
    BinNode<T>* rc;
    int height;
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0) {}
    BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* l = NULL, BinNode<T>* r = NULL, int h = 0)
        : data(e), parent(p), lc(l), rc(r), height(h) {}
    BinNode<T>* insertAsLC(const T& e) {
        return lc = new BinNode(e, this);
    }
    BinNode<T>* insertAsRC(const T& e) {
        return rc = new BinNode(e, this);
    }
};
template<typename T>
class BinTree {
protected:
    int _size;
    BinNode<T>* _root;
public:
    BinTree() : _size(0), _root(NULL) {}
    ~BinTree() { if (_size > 0) remove(_root); }
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNode<T>* root() const { return _root; }
    BinNode<T>* insertAsRoot(const T& e) {
        _size = 1;
        return _root = new BinNode<T>(e);
    }
    BinNode<T>* insertAsLC(BinNode<T>* x, const T& e) {
        _size++;
        x->insertAsLC(e);
        return x->lc;
    }
    BinNode<T>* insertAsRC(BinNode<T>* x, const T& e) {
        _size++;
        x->insertAsRC(e);
        return x->rc;
    }
    static int remove(BinNode<T>* x) {
        if (!x) return 0;
        int n = 1 + remove(x->lc) + remove(x->rc);
        delete x;
        return n;
    }
};
#endif
