#include <iostream>
#include <vector>
#include <deque>

std::vector<int64_t> min_window(std::vector<int64_t>& vec, int64_t window_size) {
    std::vector<int64_t> mins;
    std::deque<int64_t> q;

    for (int64_t i = 0; i < window_size; ++i) {
        while (!q.empty() && q.back() > vec[i]) {
            q.pop_back();
        }
        q.push_back(vec[i]);
    }

    mins.push_back(q.front());
    
    for (int64_t i = window_size; i < vec.size(); ++i) {
        if (!q.empty() && vec[i - window_size] == q.front()) {
            q.pop_front();
        }
        while (!q.empty() && q.back() > vec[i]) {
            q.pop_back();
        }
        q.push_back(vec[i]);
        mins.push_back(q.front());
    }

    return mins;
}

int main()
{
    std::vector<int64_t> vec = {2, 1, 4, 5, 3, 4, 1, 2};
    std::vector<int64_t> mins = min_window(vec, 4);

    for (auto & x : mins) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}