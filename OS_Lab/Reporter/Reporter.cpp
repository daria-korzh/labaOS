#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Reporter: Not enough arguments!" << std::endl;
        return 1;
    }

    const char* binFileName = argv[1];
    const char* reportFileName = argv[2];
    double payPerHour = std::atof(argv[3]);

    std::ifstream fin(binFileName, std::ios::binary);
    if (!fin.is_open()) {
        std::cerr << "Reporter: Error opening binary file " << binFileName << std::endl;
        return 1;
    }

    std::ofstream fout(reportFileName);
    if (!fout.is_open()) {
        std::cerr << "Reporter: Error opening report file " << reportFileName << std::endl;
        fin.close();
        return 1;
    }

    fout << "Report for file \"" << binFileName << "\"\n";
    fout << std::left << std::setw(12) << "ID"
        << std::setw(15) << "Name"
        << std::setw(12) << "Hours"
        << std::setw(12) << "Salary" << "\n";
    fout << "--------------------------------------------------\n";

    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * payPerHour;
        fout << std::left << std::setw(12) << emp.num
            << std::setw(15) << emp.name
            << std::setw(12) << emp.hours
            << std::setw(12) << std::fixed << std::setprecision(2) << salary << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}