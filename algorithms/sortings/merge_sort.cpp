#include <iostream>
#include <vector>
#include <cstdint>

const int64_t INF{INT64_MAX};

void merge(std::vector<int64_t> &vec, size_t p, size_t q, size_t r)
{
    std::vector<int64_t> L, R;
    size_t i{0}, j{0};

    for (size_t k{p}; k < q; ++k)
    {
        L.push_back(vec[k]);
    }
    for (size_t k{q}; k < r; ++k)
    {
        R.push_back(vec[k]);
    }

    for (size_t k{p}; k < r; ++k)
    {
        if (i == L.size())
        {
            vec[k] = R[j];
            ++j;
        }
        else if (j == R.size())
        {
            vec[k] = L[i];
            ++i;
        }
        else if (i != L.size() && j != R.size())
        {
            if (L[i] <= R[j])
            {
                vec[k] = L[i];
                ++i;
            }
            else
            {
                vec[k] = R[j];
                ++j;
            }
        }
        else
            break;
    }
}

void merge_sort(std::vector<int64_t> &vec, size_t p, size_t r)
{
    if (p + 1 < r)
    {
        size_t q{p + ((r - p) >> 1)};
        merge_sort(vec, p, q);
        merge_sort(vec, q, r);
        merge(vec, p, q, r);
    }
}

int main()
{
    std::vector<int64_t> vec{1, 5, 0, 2, -50};
    merge_sort(vec, 0, vec.size());

    for (size_t i{0}; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    return 0;
}
