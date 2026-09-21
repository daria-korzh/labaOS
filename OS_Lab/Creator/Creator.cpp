#include <iostream>
#include <fstream>
#include <cstdlib>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Creator: Not enough arguments!" << std::endl;
        return 1;
    }

    const char* fileName = argv[1];
    int count = std::atoi(argv[2]);

    std::ofstream fout(fileName, std::ios::binary);
    if (!fout.is_open()) {
        std::cerr << "Creator: Error opening file " << fileName << std::endl;
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp;
        std::cout << "Enter employee " << i + 1 << " details:\n";
        std::cout << "  ID (num): ";
        std::cin >> emp.num;
        std::cout << "  Name (up to 9 chars): ";
        std::cin >> emp.name;
        std::cout << "  Hours worked: ";
        std::cin >> emp.hours;

        fout.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
    }

    fout.close();
    return 0;
}