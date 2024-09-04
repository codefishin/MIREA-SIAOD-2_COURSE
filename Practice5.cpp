#include "Practice5.hpp"

int P1::Task1(int input)
{
	unsigned char x = (char)input; // привидение ввода пользователя (в int, для удобства) в char
	unsigned char mask = 1; // маска равна 00000001
	x = x & (~(mask << 4)); // двигает 4-ый бит с 1 на 0 (при 0 ничего не делает)
	return x;
}
int P1::Task2(int input)
{
	unsigned char x = (char)input; 
	unsigned char mask = 1; 
	x = x & (mask << 6); 
	return x;
}
void P1::Task3(int input)
{
	const int n = sizeof(int) * 8; // sizeof(int) -> 4 байта (размер числового) умножить на 8.  Получаем размер нашего БИТСЕТА (32)
	unsigned mask = (1 << n - 1); // маска числа 1, но мы переносим единичку на место 31-го бита (то есть 32-го, потому что программа считает с 0)
	std::cout << "Starting mask value: " << std::bitset<n>(mask) << "\nResult: "; // вывод числа маски в форме битсета
	for (int i = 1; i <= n; i++)
	{
		std::cout << ((input & mask) >> (n - i)); 
		mask = mask >> 1;
		/*
		* Здесь берётся наше число, введённое пользователем (input) и обрабатывается следующим образом
		* выводится input, использующий поразрядное И (&)
		* после результат поразрядного И переносится вправо по битам формулой N - I, i это текущий шаг, а n - размер битсета (32)
		* берётся первое число битсета числа 25 (вообще 25 = 11001 в двоичном, так что первые 27 чисел это нули.) и выполняет операцию И с маской 
		(в первом шаге она 1), после маска передвигает свои биты 1 раз направо. Следовательно 1 из маски (а маска равна единице и 31 нулю) 
		всегда двигается по битсету ввода и операция И выглядит так:
		* Текущее число ввода & 1
		* Следовательно вывод оператора И будет ВСЕГДА зависить от ввода числа. Если там 0, то выводит 0. Если там 1 выводит 1
		* короче маска тут по приколу сделана так как мы её всегда сдвигаем и для данного цикла маска не единица и 31 нуль, а 32 единицы
		*/
	}
	std::cout << '\n';
}
// Второй пункт

void P2::Task1()
{
	const int SIZE = 8;
	int num;
	unsigned char bitArr = 0;
	std::vector<int> nums;
	// ввод значений
	std::cout << "Enter values from 0 to 7.\n\nMax amount of numbers is 8.\nEnter '9' to stop.\n";
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i + 1 << " number is... ";
		std::cin >> num;

		if (num == 9) break;

		if (num >= 0 && num < 8)
		{
			nums.push_back(num);
			if (num != 0) num = SIZE - num - 1;
			else num = 7;
			bitArr |= (1 << num);
		}
		else
		{
			std::cout << "Instruction not followed";
			i--;
		}
		std::cout << '\n';
	}
	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++)
	{
		std::cout << nums[i];
	}
	std::cout << '\n' << std::bitset<SIZE>(bitArr);
}
