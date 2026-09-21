#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage: Reporter <bin_file> <report_file> <hourly_rate>" << std::endl;
        return 1;
    }

    char* binFilename = argv[1];
    char* reportFilename = argv[2];
    double hourlyRate = atof(argv[3]);

    std::ifstream fin(binFilename, std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "Error opening binary file: " << binFilename << std::endl;
        return 1;
    }

    std::ofstream fout(reportFilename);
    if (!fout.is_open())
    {
        std::cout << "Error opening report file: " << reportFilename << std::endl;
        fin.close();
        return 1;
    }

    fout << "Отчет по файлу \"" << binFilename << "\"\n";

    fout << "Номер сотрудника, имя сотрудника, часы, зарплата\n";

    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee)))
    {
        double salary = emp.hours * hourlyRate;
        fout << emp.num << ", "
            << emp.name << ", "
            << emp.hours << ", "
            << std::fixed << std::setprecision(2) << salary << "\n";
    }

    fin.close();
    fout.close();
    std::cout << "Report successfully created." << std::endl;
    return 0;
}