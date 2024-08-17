#include <iostream>
#include <numeric>
#include <vector>

/**
 * @brief Fenwick (or binary indexed) tree is a data structure that 
 *        allows to calculate certain operations on ranges of array in O(log(n)) time.
 *        To work correctly the operation must be invertible
 * 
 * @complexity O(log(n))
 */

class fenwick {
private:
    std::vector<int64_t> m_tree;
public:
    fenwick(const std::vector<int64_t>& t_vec)
        : m_tree(t_vec.size() + 1)
    {
        for (int64_t i = 1; i < m_tree.size(); ++i) {
            add(i, t_vec[i-1]);
        }
    }

    int64_t sum(int64_t a, int64_t b) {
        return sum(b) - sum(a - 1);
    }

    int64_t sum(int64_t k) {
        int64_t sum {0};

        for (; k > 0; k -= k & -k) {
            sum += m_tree[k];
        }

        return sum;
    }

    void add(int64_t k, int64_t x) {
        for (; k < m_tree.size(); k += k & -k) {
            m_tree[k] += x;
        }
    }
};

int main() {
    std::vector<int64_t> vec {1, 3, 4, 8, 6, 1, 4, 2};

    fenwick tree(vec);
    std::cout << tree.sum(0, vec.size()) << std::endl;
}