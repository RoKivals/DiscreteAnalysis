#include "CountingSort.h"

// GetKey - Функция, которая вытаскивает ключ из пары
template<class T>
void CountingSort(Vector<T> &data, std::function<size_t(T)> GetKey) {
    if (data.Size() <= 1) return;

    size_t max_key = 0;
    for (size_t i(0); i < data.Size(); ++i) {
        max_key = std::max(max_key, GetKey(data[i]));
    }

    // Создаём вектор для хранения кол-ва ключей с одинаковым индексом
    Vector<size_t> count_keys(max_key + 1, 0);
    for (size_t i(0); i < data.Size(); ++i) {
        ++count_keys[GetKey(data[i])];
    }

    // Создаём массив, в котором каждый элемент указывает на последний подходящий для этого ключа индекс
    for (size_t i(1); i < count_keys.Size(); ++i) {
        count_keys[i] += count_keys[i - 1];
    }

    // Результирующий вектор
    Vector<T> res(data.Size());
    // Размещаем элементы с конца для сохранения порядка ввода
    for (int64_t i = data.Size() - 1; i >= 0; --i) {
        res[--count_keys[GetVal(data[i])]] = data[i];
    }

    data = std::move(res);
}
