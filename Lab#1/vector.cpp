#include "vector.h"


template<class T>
Vector<T>::Vector() {
    _size = 0;
    _capacity = 10;
    _data = new T[_capacity];
}

template<class T>
Vector<T>::Vector(const size_t &size, const T &data) {
    _size = size;
    _capacity = _size * 2;
    _data = new T[_capacity];
    for (size_t i(0); i < _size; ++i) {
        _data[i] = data;
    }
}

template<class T>
Vector<T>::Vector(Vector<T> &another) {
    _size = another._size;
    _capacity = another._capacity;
    _data = new T[_capacity];
    for (size_t i(0); i < _size; ++i) {
        _data[i] = another._data[i];
    }
}

template<class T>
Vector<T>::~Vector() {
    delete[] _data;
}

template<class T>
size_t Vector<T>::Size() {
    return _size;
}

template<class T>
bool Vector<T>::Empty() {
    return _size == 0;
}

template<class T>
void Vector<T>::PushBack(const T &value) {
    if (_size >= _capacity) {
        Reallocate();
    }
    _data[_size] = value;
    ++_size;
}

template<class T>
T Vector<T>::PopBack() {
    --_size;
    return _data[_size + 1];
}

template<class T>
void Vector<T>::Set(size_t pos, const T &value) {
    _data[pos] = value;
}

template<class T>
T &Vector<T>::operator[](size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Invalid index");
    }
    return _data[pos];
}

template<class T>
T *Vector<T>::Begin() {
    return &_data[0];
}

template<class T>
T *Vector<T>::End() {
    return &_data[_size - 1];
}

template<class T>
void Vector<T>::Reallocate() {
    T *new_data = new T[_capacity * GROWTH_COEF];

    for (unsigned int i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
    }

    delete[] _data;
    _capacity = _capacity * GROWTH_COEF;
    _data = new_data;
}
