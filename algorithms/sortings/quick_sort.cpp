#include <iostream>
#include <vector>

int64_t partition(std::vector<int64_t> &vec, int64_t p, int64_t r)
{
    int64_t x{vec[r]};
    int64_t i{p - 1};

    for (int64_t j{p}; j < r; ++j)
    {
        if (vec[j] <= x)
        {
            std::swap(vec[j], vec[++i]);
        }
    }

    std::swap(vec[++i], vec[r]);
    return i == r ? p + ((r - p) >> 1) : i;
}

void quick_sort(std::vector<int64_t> &vec, int64_t p, int64_t r)
{
    if (p < r)
    {
        int64_t q{partition(vec, p, r)};
        quick_sort(vec, p, q - 1);
        quick_sort(vec, q + 1, r);
    }
}

int main()
{
    std::vector<int64_t> vec{2, 2, 2, 2, 3, -10};
    quick_sort(vec, 0, vec.size() - 1);
    for (auto &x : vec)
    {
        std::cout << x << " ";
    }

    return 0;
}
