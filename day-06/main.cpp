#include <iostream>
#include <unordered_set>
#include <deque>

void solve(size_t size) {
    std::deque<char> buf;
    char c;
    int i = 1;
    while (std::cin >> c) {
        if (buf.size() == size) buf.pop_front();
        buf.push_back(c);
        if (buf.size() == size && std::unordered_set<char>(buf.cbegin(), buf.cend()).size() == size) {
            std::cout << i << '\n';
            return;
        }
        ++i;
    }
}

void part_1() {
    solve(4);
}

void part_2() {
    solve(14);
}

int main() {
//     part_1(); // 1262
    part_2(); // 3444
    return 0;
}
