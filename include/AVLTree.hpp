#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

class AVLNode {
public:
    int key;
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, int v);
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balance(AVLNode* node);
    AVLNode* insert(AVLNode* node, int key, int value);
    AVLNode* findMin(AVLNode* node) const;
    AVLNode* remove(AVLNode* node, int key);
    void clear(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(int key, int value);
    bool remove(int key);
    bool contains(int key) const;
};

#endif // AVL_TREE_HPP