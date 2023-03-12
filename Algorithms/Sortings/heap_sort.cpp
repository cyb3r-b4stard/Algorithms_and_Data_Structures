#include <iostream>
#include <vector>

int64_t parent(int64_t i) { return (i - 1) >> 1;       }
int64_t left(int64_t i)   { return (i << 1) + 1; }
int64_t right(int64_t i)  { return (i << 1) + 2; }

template <typename T>
void max_heapify(std::vector<T> & array, int64_t i, int64_t size) {
    int64_t l { left(i) }, 
            r { right(i) },
            largest, j { i };

    while (l < size || r < size) {
        if (l < size && array[l] > array[j])
            largest = l;
        else
            largest = j;
        if (r < size && array[r] > array[largest])
            largest = r;
        if (largest != j) {
            std::swap(array[j], array[largest]);
            j = largest;
        } else break;
        l = left(j);
        r = right(j);
    }
}

template <typename T>
void build_max_heap(std::vector<T> & array) {
    for (int64_t i = array.size() / 2; i >= 0; --i)
        max_heapify(array, i, array.size());
}

template <typename T>
void heap_sort(std::vector<T> & array) {
    int64_t size { array.size() };
    build_max_heap(array);
    for (int64_t i = array.size() - 1; i > 0; --i) {
        std::swap(array[0], array[i]);
        max_heapify(array, 0, --size);
    }
}


int main() {
    std::vector<int64_t> vec {2, 4, 1, 8, 7, 9, 3, 14, 10, 16};
    heap_sort(vec);
    for (auto & x : vec)
        std::cout << x << " ";

    return 0;
}
