#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

int main() {
    auto ifs = std::ifstream();
    ifs.open("input.txt");

    const auto points = std::unordered_map<char, uint64_t>{{'A', 1},
                                                           {'B', 2},
                                                           {'C', 3}};
    const auto lose = std::unordered_map<char, char>{{'A', 'C'},
                                                     {'B', 'A'},
                                                     {'C', 'B'}};
    const auto win = std::unordered_map<char, char>{{'A', 'B'},
                                                    {'B', 'C'},
                                                    {'C', 'A'}};

    auto line = std::string();
    auto score = static_cast<uint64_t>(0);

    while (std::getline(ifs, line)) {
        auto ss = std::istringstream(line);

        char elf;
        char result;
        ss >> elf >> result;

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
    return 0;
}
