#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct employee {
    int num;
    char name[10];
    double hours;
};

bool RunProcess(const std::string& commandLine) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    std::string cmd = commandLine;

    if (!CreateProcessA(
        NULL,
        &cmd[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    ))
    {
        std::cerr << "Main: Failed to create process! Error code: " << GetLastError() << std::endl;
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return true;
}

void DisplayBinaryFile(const std::string& fileName) {
    std::ifstream fin(fileName, std::ios::binary);
    if (!fin.is_open()) {
        std::cerr << "Main: Error reading binary file: " << fileName << std::endl;
        return;
    }

    std::cout << "\n--- Binary File Content (" << fileName << ") ---\n";
    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << "ID: " << emp.num
            << " | Name: " << emp.name
            << " | Hours: " << emp.hours << "\n";
    }
    fin.close();
    std::cout << "-------------------------------------------\n\n";
}

void DisplayTextFile(const std::string& fileName) {
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cerr << "Main: Error reading report file: " << fileName << std::endl;
        return;
    }

    std::cout << "\n=== Output Report File Content (" << fileName << ") ===\n";
    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << "\n";
    }
    fin.close();
    std::cout << "=================================================\n\n";
}

int main() {
    std::string binFileName;
    int recordCount;

    std::cout << "Enter binary file name: ";
    std::cin >> binFileName;
    std::cout << "Enter number of records: ";
    std::cin >> recordCount;

    std::string creatorCmd = "Creator.exe " + binFileName + " " + std::to_string(recordCount);
    if (!RunProcess(creatorCmd)) {
        return 1;
    }

    DisplayBinaryFile(binFileName);

    std::string reportFileName;
    double payPerHour;
    std::cout << "Enter report text file name: ";
    std::cin >> reportFileName;
    std::cout << "Enter pay per hour: ";
    std::cin >> payPerHour;

    std::string reporterCmd = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(payPerHour);
    if (!RunProcess(reporterCmd)) {
        return 1;
    }

    DisplayTextFile(reportFileName);

    return 0;
}