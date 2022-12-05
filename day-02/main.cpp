#include <iostream>
#include <unordered_map>

void part_1() {
    static const auto points = std::unordered_map<char, int>{{'A', 1},
                                                             {'B', 2},
                                                             {'C', 3},
                                                             {'X', 1},
                                                             {'Y', 2},
                                                             {'Z', 3}};

    int score = 0;
    char elf, you;

    while (std::cin >> elf >> you) {
        score += points.at(you);
        if ((you == 'X' && elf == 'A') || (you == 'Y' && elf == 'B') || (you == 'Z' && elf == 'C')) {
            score += 3;
        } else if ((you == 'X' && elf == 'C') || (you == 'Y' && elf == 'A') || (you == 'Z' && elf == 'B')) {
            score += 6;
        }
    }

    std::cout << score << '\n';
}

void part_2() {
    static const auto points = std::unordered_map<char, int>{{'A', 1},
                                                             {'B', 2},
                                                             {'C', 3}};
    static const auto lose = std::unordered_map<char, char>{{'A', 'C'},
                                                            {'B', 'A'},
                                                            {'C', 'B'}};
    static const auto win = std::unordered_map<char, char>{{'A', 'B'},
                                                           {'B', 'C'},
                                                           {'C', 'A'}};

    char elf, result;
    int score = 0;

    while (std::cin >> elf >> result) {
        if (result == 'X') {
            score += points.at(lose.at(elf));
        } else if (result == 'Y') {
            score += 3;
            score += points.at(elf);
        } else if (result == 'Z') {
            score += 6;
            score += points.at(win.at(elf));
        }
    }

    std::cout << score << '\n';
}

int main() {
    part_1(); // 11475
//    part_2(); // 16862
    return 0;
}
