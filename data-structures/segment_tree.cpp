#include <iostream>
#include <vector>

void build(std::vector<int64_t> &tree, std::vector<int64_t> &init, int64_t l, int64_t r, int64_t index)
{
    if (l + 1 == r)
    {
        tree[index] = init[l];
    }
    else
    {
        int64_t m = l + ((r - l) >> 1);
        build(tree, init, l, m, 2 * index);
        build(tree, init, m, r, 2 * index + 1);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
}

int64_t sum(std::vector<int64_t> &tree, int64_t l, int64_t r, int64_t a, int64_t b, int64_t index)
{
    if (b <= l || r <= a)
    {
        return 0;
    }

    if (a <= l && r <= b)
    {
        return tree[index];
    }

    int64_t m = l + ((r - l) >> 1);

    return sum(tree, l, m, a, b, 2 * index) +
           sum(tree, m, r, a, b, 2 * index + 1);
}

int main()
{
    return 0;
}
