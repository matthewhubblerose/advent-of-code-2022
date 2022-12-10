#include <iostream>
#include <string>

int add_value(int cycle, int x) {
    return (cycle - 20) % 40 == 0 ? cycle * x : 0;
}

void part_1() {
    std::string instruction;
    int value, x = 1, cycle = 0, total = 0;

    while (std::cin >> instruction) {
        if (instruction == "noop") {
            ++cycle;
           total += add_value(cycle, x);
        } else {
            std::cin >> value;
            ++cycle;
            total += add_value(cycle, x);
            ++cycle;
            total += add_value(cycle, x);
            x += value;
        }
    }

    std::cout << total << '\n';
}

void print_pixel(int cycle, int x) {
    const int pos = cycle % 40;
    if (pos == 0) std::cout << '\n';
    const char c = (x >= pos - 1 && x <= pos + 1) ? '#' : '.';
    std::cout << c;
}

void part_2() {
    std::string instruction;
    int value, x = 1, cycle = 0;

    while (std::cin >> instruction) {
        if (instruction == "noop") {
            print_pixel(cycle, x);
            ++cycle;
        } else {
            std::cin >> value;
            print_pixel(cycle, x);
            ++cycle;
            print_pixel(cycle, x);
            ++cycle;
            x += value;
        }
    }
}

int main() {
//    part_1(); // 14240
    part_2(); // PLULKBZH
    return 0;
}
