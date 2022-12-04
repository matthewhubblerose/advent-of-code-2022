#include <iostream>

void part_1() {
    int s1, e1, s2, e2, res = 0;
    char c;

    while (std::cin >> s1 >> c >> e1 >> c >> s2 >> c >> e2) {
        if ((s2 >= s1 && e2 <= e1) || (s1 >= s2 && e1 <= e2)) {
            ++res;
        }
    }

    std::cout << res << '\n';
}

void part_2() {
    int s1, e1, s2, e2, res = 0;
    char c;

    while (std::cin >> s1 >> c >> e1 >> c >> s2 >> c >> e2) {
        if ((s2 >= s1 && s2 <= e1) || (e2 >= s1 && e2 <= e1) ||
            (s1 >= s2 && s1 <= e2) || (e1 >= s2 && e1 <= e2)) {
            ++res;
        }
    }

    std::cout << res << '\n';
}

int main() {
    part_1();
//    part_2();
    return 0;
}
