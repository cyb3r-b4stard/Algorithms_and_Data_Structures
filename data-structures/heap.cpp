#include <iostream>
#include <vector>

/**
 * @brief Binary tree that supports efficient retrieval of maximum (or minimum) element
 *
 * @complexity Builds heap in O(n), inserts element and extracts
 *             maximum (or minimum) in O(log(n)), returns maximum (or minimum) in O(1)
 */
template <typename T>
class Heap
{
public:
    Heap() = default;
    Heap(const std::initializer_list<T> &lst)
        : array(new T[lst.size()]), length(lst.size()), size(lst.size())
    {
        for (int64_t i{0}; i < lst.size(); ++i)
        {
            array[i] = *(lst.begin() + i);
        }

        for (int64_t j{length >> 1}; j >= 0; --j)
        {
            this->max_heapify(j);
        }
    }

    Heap(const std::vector<T> &vec)
        : array(new T[vec.size()]), length(vec.size()), size(vec.size())
    {
        for (int64_t i{0}; i < vec.size(); ++i)
        {
            array[i] = *(vec.begin() + i);
        }

        for (int64_t j{length >> 1}; j >= 0; --j)
        {
            this->max_heapify(j);
        }
    }

    ~Heap() { delete[] array; }

    void insert(T key)
    {
        if (size == length)
        {
            T *temp_array{new T[length * 2]};

            for (int64_t i{0}; i < size; ++i)
            {
                temp_array[i] = array[i];
            }

            delete[] array;

            array = temp_array;
            length *= 2;
        }

        array[size++] = key;

        int64_t i{size - 1};

        while (i > 0 && array[parent(i)] < array[i])
        {
            std::swap(array[i], array[parent(i)]);
            i = parent(i);
        }
    }

    void print()
    {
        for (size_t i{0}; i < size; ++i)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }

    void max_heapify(int64_t i)
    {
        int64_t left{this->left(i)};
        int64_t right{this->right(i)};
        int64_t largest, j{i};

        while (left < size || right < size)
        {
            if (left < size && array[left] > array[j])
            {
                largest = left;
            }
            else
            {
                largest = j;
            }

            if (right < size && array[right] > array[largest])
            {
                largest = right;
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

            left = this->left(j);
            right = this->right(j);
        }
    }

    T extract_max()
    {
        if (size == 0)
        {
            throw std::out_of_range("Heap is empty");
        }

        T max{array[0]};

        std::swap(array[0], array[--size]);

        max_heapify(0);

        return max;
    }

    T max()
    {
        if (size == 0)
        {
            throw std::out_of_range("Heap is empty");
        }

        return array[0];
    }

    int64_t parent(int64_t i) { return (i - 1) >> 1; }
    int64_t left(int64_t i) { return (i << 1) + 1; }
    int64_t right(int64_t i) { return (i << 1) + 2; }

private:
    T *array{new T[8]};
    int64_t length{8};
    int64_t size{0};
};

int main()
{
    Heap<int64_t> h;
    return 0;
}
