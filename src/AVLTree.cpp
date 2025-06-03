#include "AVLTree.hpp"
#include <algorithm>

// Konstruktor węzła AVL - inicjalizuje klucz, wartość i ustawia wysokość na 1
AVLNode::AVLNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}

// Konstruktor drzewa AVL - inicjalizuje pusty korzeń
AVLTree::AVLTree() : root(nullptr) {}

// Destruktor - czyści rekurencyjnie całe drzewo
AVLTree::~AVLTree() {
    clear(root);
}

// Zwraca wysokość poddrzewa (0 dla nullptr)
int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

// Oblicza współczynnik balansu węzła (różnica wysokości poddrzew)
int AVLTree::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

// Aktualizuje wysokość węzła na podstawie poddrzew
void AVLTree::updateHeight(AVLNode* node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}

// Rotacja w prawo (do balansowania drzewa)
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotacja w lewo (do balansowania drzewa)
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balansuje poddrzewo i zwraca nowy korzeń
AVLNode* AVLTree::balance(AVLNode* node) {
    updateHeight(node);

    // Lewa nierównowaga
    if (balanceFactor(node) > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // Lewo-prawa
        }
        return rotateRight(node); // Lewo-lewa
    }

    // Prawa nierównowaga
    if (balanceFactor(node) < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right); // Prawo-lewa
        }
        return rotateLeft(node); // Prawo-prawa
    }

    return node; // Drzewo zbalansowane
}

// Rekurencyjne wstawianie węzła
AVLNode* AVLTree::insert(AVLNode* node, int key, int value) {
    if (!node) return new AVLNode(key, value); // Nowy węzeł

    if (key < node->key) {
        node->left = insert(node->left, key, value); // Wstaw do lewego poddrzewa
    } else if (key > node->key) {
        node->right = insert(node->right, key, value); // Wstaw do prawego poddrzewa
    } else {
        node->value = value; // Aktualizacja istniejącej wartości
        return node;
    }

    return balance(node); // Zbalansuj drzewo
}

// Znajduje minimalny węzeł w poddrzewie
AVLNode* AVLTree::findMin(AVLNode* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Rekurencyjne usuwanie węzła
AVLNode* AVLTree::remove(AVLNode* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key); // Szukaj w lewym poddrzewie
    } else if (key > node->key) {
        node->right = remove(node->right, key); // Szukaj w prawym poddrzewie
    } else {
        // Węzeł do usunięcia znaleziony
        if (!node->left || !node->right) {
            // Przypadek z 0 lub 1 dzieckiem
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp; // Skopiuj dziecko
            }
            delete temp;
        } else {
            // Przypadek z 2 dziećmi - znajdź następnik
            AVLNode* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key); // Usuń następnik
        }
    }

    if (!node) return nullptr;

    return balance(node); // Zbalansuj drzewo
}

// Rekurencyjne czyszczenie drzewa
void AVLTree::clear(AVLNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Publiczne metody interfejsu:

void AVLTree::insert(int key, int value) {
    root = insert(root, key, value);
}

bool AVLTree::remove(int key) {
    if (!contains(key)) return false;
    root = remove(root, key);
    return true;
}

bool AVLTree::contains(int key) const {
    AVLNode* current = root;
    while (current) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return true;
        }
    }
    return false;
}