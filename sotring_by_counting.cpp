/*
 * Сортировка подсчётом (sort by counting) - Устойчивая сортировка за O(n^2)
 */
#include <iostream>
#include <vector>

/*
 * Ключ - int32
 * Значение - char
 */
struct KV {
public:
    int32_t key;
    char value;

    KV() = default;

    KV(int32_t i, char i1) : key(i), value(i1) {};
};


void CountingSort(const std::vector<KV> &input, int32_t max_key, std::vector<KV> &result) {
    if (input.empty()) {
        return;
    }
    result.resize(input.size());
    std::vector<size_t> B(max_key + 1, 0);
    for (auto kv: input) {
        B[kv.key] += 1;
    }

    for (size_t i(1); i < B.size(); ++i) {
        B[i] += B[i - 1];
    }

    for (int32_t i(input.size() - 1); i >= 0; --i) {
        size_t index = B[input[i].key] - 1;
        result[index] = input[i];
        --B[input[i].key];
    }
}

int main() {
    std::vector<KV> input;
    int32_t key, max_key = 0;
    char value;
    while (std::cin >> key >> value) {
        input.emplace_back(key, value);
        max_key = std::max(max_key, key);
    }

    for (auto elem: input) {
        std::cout << "Key: " << elem.key << " value: " << elem.value << '\n';
    }
    return 0;
}
