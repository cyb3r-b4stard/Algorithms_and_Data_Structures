#include <iostream>
#include <vector>

inline size_t parent(size_t i) { return (i - 1) >> 1; }
inline size_t left(size_t i) { return (i << 1) + 1; }
inline size_t right(size_t i) { return (i << 1) + 2; }

void max_heapify(std::vector<int64_t> &array, size_t i, size_t size)
{
    size_t l{left(i)}, r{right(i)}, largest, j{i};

    while (l < size || r < size)
    {
        if (l < size && array[l] > array[j])
        {
            largest = l;
        }
        else
        {
            largest = j;
        }

        if (r < size && array[r] > array[largest])
        {
            largest = r;
        }

        if (largest != j)
        {
            std::swap(array[j], array[largest]);
            j = largest;
        }
        else
        {
            break;
        }

        l = left(j);
        r = right(j);
    }
}

void build_max_heap(std::vector<int64_t> &array)
{
    size_t size{array.size()};

    for (size_t i{size >> 1}; i >= 0; --i)
    {
        max_heapify(array, i, size);
    }
}

void heap_sort(std::vector<int64_t> &array)
{
    size_t size{array.size()};

    build_max_heap(array);

    for (size_t i{size - 1}; i > 0; --i)
    {
        std::swap(array[0], array[i]);nt64_t>
        max_heapify(array, 0, --size);
    }
}

int main()
{
    std::vector<int64_t> vec{2, 4, 1, 8, 7, 9, 3, 14, 10, 16};

    heap_sort(vec);

    for (auto &x : vec)
    {
        std::cout << x << " ";
    }

    return 0;
}
