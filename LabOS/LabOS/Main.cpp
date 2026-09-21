#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    
    std::string binFilename;
    int recordsCount;

    std::cout << "Введите имя бинарного файла: ";
    std::cin >> binFilename;
    std::cout << "Введите количество записей: ";
    std::cin >> recordsCount;

    
    std::string creatorCmd = "Creator.exe " + binFilename + " " + std::to_string(recordsCount);

    STARTUPINFOA siCreator;
    PROCESS_INFORMATION piCreator;
    ZeroMemory(&siCreator, sizeof(STARTUPINFOA));
    siCreator.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&piCreator, sizeof(PROCESS_INFORMATION));

    if (!CreateProcessA(
        NULL,
        const_cast<char*>(creatorCmd.c_str()),
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE, 
        NULL,
        NULL,
        &siCreator,
        &piCreator))
    {
        std::cout << "Ошибка при запуске Creator. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    
    WaitForSingleObject(piCreator.hProcess, INFINITE);
    CloseHandle(piCreator.hThread);
    CloseHandle(piCreator.hProcess);

    
    std::cout << "\nСодержимое бинарного файла " << binFilename << ":\n";
    std::ifstream fin(binFilename, std::ios::binary);
    if (fin.is_open())
    {
        employee emp;
        while (fin.read(reinterpret_cast<char*>(&emp), sizeof(employee)))
        {
            std::cout << "ID: " << emp.num
                << ", Имя: " << emp.name
                << ", Часы: " << emp.hours << std::endl;
        }
        fin.close();
    }
    else
    {
        std::cout << "Не удалось открыть бинарный файл для чтения.\n";
    }

  
    std::string reportFilename;
    double hourlyRate;

    std::cout << "\nВведите имя файла отчета: ";
    std::cin >> reportFilename;
    std::cout << "Введите оплату за час работы: ";
    std::cin >> hourlyRate;

    
    std::string reporterCmd = "Reporter.exe " + binFilename + " " + reportFilename + " " + std::to_string(hourlyRate);

    STARTUPINFOA siReporter;
    PROCESS_INFORMATION piReporter;
    ZeroMemory(&siReporter, sizeof(STARTUPINFOA));
    siReporter.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&piReporter, sizeof(PROCESS_INFORMATION));

    if (!CreateProcessA(
        NULL,
        const_cast<char*>(reporterCmd.c_str()),
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &siReporter,
        &piReporter))
    {
        std::cout << "Ошибка при запуске Reporter. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

   
    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hThread);
    CloseHandle(piReporter.hProcess);


    std::cout << "\nСодержимое файла отчета " << reportFilename << ":\n";
    std::ifstream fReport(reportFilename);
    if (fReport.is_open())
    {
        std::string line;
        while (std::getline(fReport, line))
        {
            std::cout << line << std::endl;
        }
        fReport.close();
    }
    else
    {
        std::cout << "Не удалось открыть файл отчета для чтения.\n";
    }

    return 0;
}