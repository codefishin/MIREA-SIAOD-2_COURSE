#include <iostream>
#include "Practice5.hpp"
#include <chrono>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    auto time = std::chrono::high_resolution_clock::now();

    /*int input;
    std::cin >> input;*/
    // для первых программ нужен input ^

    P1 Program1;
    P2 Program2;
    P3 Program3;

    //Program3.SpamFile();
    //Program3.Task1();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - time).count();
    std::cout << "Time: " << dur << "mil\n";
}
