#include "CountingSort.h"

template<class T, class Y> struct Pair {
    T first;
    Y second;
};

template<class T, class Y>
std::istream &operator>>(std::istream &in, Pair<T, Y> &p) {
    in >> p.first >> p.second;
    return in;
}

// GetKey - Функция, которая вытаскивает ключ из пары
template<class T>
void CountingSort(Vector<T> &data, std::function<size_t(T)> GetKey) {
    if (data.Size() <= 1) return;

    size_t max_key = 0;
    for (size_t i(0); i < data.Size(); ++i) {
        max_key = std::max(max_key, GetKey(data[i]));
    }

    // Создаём вектор для хранения ключей по порядку
    Vector<size_t> keys(max_key + 1, 0);
}
