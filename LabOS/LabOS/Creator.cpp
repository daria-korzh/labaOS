#include <windows.h>
#include <iostream>
#include <fstream>

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: Creator <bin_filename> <records_count>" << std::endl;
        return 1;
    }

    char* filename = argv[1];
    int count = atoi(argv[2]);

    std::ofstream fout(filename, std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::cout << "=== Creator Utility ===" << std::endl;
    for (int i = 0; i < count; ++i)
    {
        employee emp;
        std::cout << "Enter details for employee " << (i + 1) << ":" << std::endl;
        std::cout << "ID: ";
        std::cin >> emp.num;
        std::cout << "Name (up to 9 chars): ";
        std::cin >> emp.name;
        std::cout << "Hours: ";
        std::cin >> emp.hours;

        fout.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    fout.close();
    std::cout << "Binary file successfully created." << std::endl;
    return 0;
}