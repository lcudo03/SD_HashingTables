#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize(int newCapacity);

public:
    Array(int initialCapacity = 10);
    ~Array();

    void push_back(const T& value);
    T& operator[](int index);
    const T& operator[](int index) const;
    int size() const;
    void clear();
};

template <typename T>
void Array<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < currentSize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
Array<T>::Array(int initialCapacity) : capacity(initialCapacity), currentSize(0) {
    data = new T[capacity];
}

template <typename T>
Array<T>::~Array() {
    delete[] data;
}

template <typename T>
void Array<T>::push_back(const T& value) {
    if (currentSize == capacity) {
        resize(capacity * 2);
    }
    data[currentSize++] = value;
}

template <typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
int Array<T>::size() const {
    return currentSize;
}

template <typename T>
void Array<T>::clear() {
    currentSize = 0;
}

#endif // ARRAY_HPP