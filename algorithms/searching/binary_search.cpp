#include <iostream>
#include <vector>

size_t lower_bound(const std::vector<int64_t> &vec, int64_t value)
{
    size_t l{0}, r{vec.size()}, mid;

    while (l < r)
    {
        mid = (l + r) >> 1;

        if (vec[mid] < value)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

size_t upper_bound(const std::vector<int64_t> &vec, int64_t value)
{
    size_t l{0}, r{vec.size()}, mid;

    while (l < r)
    {
        mid = (l + r) >> 1;

        if (vec[mid] <= value)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

int main()
{
    std::vector<int64_t> vec{1, 2, 3, 4};
    std::cout << lower_bound(vec, 0) << std::endl;
    std::cout << upper_bound(vec, 0) << std::endl;
    return 0;
}
