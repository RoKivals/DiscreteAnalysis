#ifndef DISKRETANALYSIS_VECTOR_H
#define DISKRETANALYSIS_VECTOR_H

#include <iostream>

template<class T>
class Vector {
    // _capacity - allocated memory, _size - cnt elements
    size_t _capacity;
    size_t _size;
    T *_data;
    const size_t GROWTH_COEF = 2;
    void Reallocate();

public:
    // Con/De-structor
    Vector();
    Vector(const size_t &, const T &);
    Vector(Vector<T> &);
    ~Vector();

    // Methods
    size_t Size();
    bool Empty();
    void PushBack(const T&);
    T PopBack();
    void Set(size_t, const T&);
    T& operator[](size_t);
    T* Begin();
    T* End();
};



#endif //DISKRETANALYSIS_VECTOR_H
