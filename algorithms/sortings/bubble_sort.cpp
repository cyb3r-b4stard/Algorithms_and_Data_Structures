#include <iostream>
#include <vector>

void bubble_sort(std::vector<int64_t> &vec)
{
    for (size_t i{0}; i < vec.size(); ++i)
    {
        for (size_t j{0}; j + 1 < vec.size(); ++j)
        {
            if (vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
        }
    }
}

int main()
{
    std::vector<int64_t> vec{1, 5, 10, 3, 0, -2};
    bubble_sort<int64_t>(vec);
    for (size_t i{0}; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    return 0;
}