#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    LinkedList();
    ~LinkedList();

    void push_back(const T& value);
    bool remove(const T& value);
    void clear();
    int size() const;

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        
        T& operator*() { return current->data; }
        T* operator->() { return &current->data; }
        
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    listSize++;
}

template <typename T>
bool LinkedList<T>::remove(const T& value) {
    Node* current = head;
    Node* prev = nullptr;

    while (current) {
        if (current->data == value) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current == tail) {
                tail = prev;
            }

            delete current;
            listSize--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    listSize = 0;
}

template <typename T>
int LinkedList<T>::size() const {
    return listSize;
}

#endif // LINKED_LIST_HPP