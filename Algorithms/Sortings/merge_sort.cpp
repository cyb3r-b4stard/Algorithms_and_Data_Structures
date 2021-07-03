#include <algorithm>
#include <iostream>
#include <vector>
#define inf 1e9

template <typename T>
void merge(std::vector<T> &vec, int64_t p, int64_t q, int64_t r) {

    std::vector<T> L, R;
    int64_t i = 0, j = 0;
    for (int64_t i = p; i < q + 1; ++i) {
        L.push_back(vec[i]);
    }
    for (int64_t i = q + 1 ; i < r + 1; ++i) {
        R.push_back(vec[i]);
    }

    for (int64_t k = p; k < r + 1; ++k) {
        if (i == L.size()) {
            vec[k] = R[j];
            ++j;
        } else if (j == R.size()) {
            vec[k] = L[i];
            ++i;
        } else if (i != L.size() && j != R.size()) {
            if (L[i] <= R[j]) {
                vec[k] = L[i];
                ++i;
            } else {
                vec[k] = R[j];
                ++j;
            }
        } else break;
    }
}

template <typename T>
void merge_sort(std::vector<T> &vec, int64_t p, int64_t r) {
    if (p < r) {
    int64_t q = (p + r) / 2;
    merge_sort(vec, p, q);
    merge_sort(vec, q + 1, r);
    merge(vec, p, q, r);
    }
}

int main() {
    std::vector<int64_t> vec {1, 5, 0, 2, -50};
    merge_sort<int64_t> (vec, 0, vec.size()-1);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    return 0;
}