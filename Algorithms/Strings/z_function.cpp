#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Calculates the z-function of a given string, that is, an array 
 *        z such that z[i] = maximum length of substring s[i:j] which equals to
 *        prefix of same length
 * 
 * @complexity O(n)
 */

std::vector<int> z_function(std::string& str) {
    std::vector<int> z (str.size());
    int l (0), r (0);

    for (int i = 1; i < str.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);

        while (z[i] + i < str.size() && str[z[i]] == str[z[i] + i]) ++z[i];

        if (z[i] + i - 1 > r) {
            l = i;
            r = z[i] + i - 1;
        }
    }

    return z;
}


int main() {
    std::string str;
    std::cin >> str;

    std::vector<int> vec = z_function(str);

    for (auto x : vec) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}