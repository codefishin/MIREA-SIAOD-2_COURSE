#include "Practice5.hpp"

int P1::Task1(int input)
{
	unsigned char x = (char)input;
	unsigned char mask = 1; 
	x = x & (~(mask << 4)); 
	return x;
}
int P1::Task2(int input)
{
	unsigned char x = char(input);
	unsigned char mask = 1;
	mask = mask << 6;
	x = x & (~(mask));
	x = x | mask;
	return x;
}
void P1::Task3(int input)
{
	const int n = sizeof(int) * 8;
	unsigned mask = (1 << n - 1);
	std::cout << "Starting mask value: " << std::bitset<n>(mask) << "\nResult: ";
	for (int i = 1; i <= n; i++)
	{
		std::cout << ((input & mask) >> (n - i));
		mask = mask >> 1;
	}
	std::cout << '\n';
}
// Второй пункт

void P2::Task1()
{
	const int SIZE = 8;
	int num;
	unsigned char bitArr = 0;
	// ввод значений
	std::cout << "Enter values from 0 to 7.\n\nMax amount of numbers is 8.\nEnter '9' to stop.\n";
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i + 1 << " number is... ";
		std::cin >> num;

		if (num == 9) break;

		if (num >= 0 && num < 8)
		{
			bitArr |= (1 << num);
		}
		else
		{
			std::cout << "Instruction not followed";
			i--;
		}
		std::cout << '\n';
	}
	std::cout << '\n' << std::bitset<SIZE>(bitArr) << '\n';
	for (int i = 0; i < SIZE; i++)
	{
		if (bitArr & (1 << i))
		{
			std::cout << i << " ";
		}
	}
}
void P2::Task2()
{
	const int SIZE = 64;
	int num;
	unsigned long long bitArr = 0;
	// ввод значений
	std::cout << "Enter values from 0 to 63.\n\nMax amount of numbers is 64.\nEnter '65' to stop.\n";

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i + 1 << " number is... ";
		std::cin >> num;

		if (num == 65) break;

		if (num >= 0 && num < 64)
		{
			bitArr |= (1ULL << num);
		}
		else
		{
			std::cout << "Instruction not followed";
			i--;
		}
		std::cout << '\n';
	}

	std::cout << '\n' << std::bitset<SIZE>(bitArr) << '\n';

	for (int i = 0; i < SIZE; i++)
	{
		if (bitArr & (1ULL << i))
		{
			std::cout << i << " ";
		}
	}
}
void P2::Task3()
{
	const int SIZE = 64;
	int num;
	unsigned char bitArr[SIZE / 8]{};
	for (int i = 0; i < 8; i++) bitArr[i] = int(0); // инициализация
	int temp = 0;
	// ввод значений
	std::cout << "Enter values from 0 to 63.\n\nMax amount of numbers is 64.\nEnter '65' to stop.\n";

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << i + 1 << " number is... ";
		std::cin >> num;

		if (num == 65) break;

		if (num >= 0 && num < 64)
		{
			temp = num / 8;
			bitArr[temp] |= (1 << num % 8);
		}
		else
		{
			std::cout << "Instruction not followed";
			i--;
		}
		std::cout << '\n';
	}

	std::cout << '\n';
	for (int i = SIZE / 8 - 1; i >= 0; i--)	std::cout << std::bitset<SIZE / 8>(bitArr[i]) << ' ';
	std::cout << '\n';

	for (int i = 0; i < SIZE / 8; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (bitArr[i] & (1 << y))
			{
				std::cout << y + i * 8 << " ";
			}
		}
	}
}

// Третий пункт

void P3::SpamFile()
{
	int _SIZE = 10000000;
	std::ofstream o_data("C:\\Users\\Alex\\source\\repos\\SIAOD\\Data.txt");
	for (int i = 0; i < _SIZE; i++)
	{
		o_data << rand() << '\n';
	}
}
void P3::Task1()
{
	std::ifstream i_data("C:\\Users\\Alex\\source\\repos\\SIAOD\\Data.txt");
	unsigned long long buffer = 0;
	int maxSize = 10000000, bitArrPos;
	std::vector<unsigned long long> bitArr(maxSize / 64, 0);
	while (i_data >> buffer)
	{
		bitArrPos = buffer / 64;
		bitArr[bitArrPos] |= (1ULL << buffer % 64);
	}
	std::ofstream o_data("C:\\Users\\Alex\\source\\repos\\SIAOD\\Data.txt", std::ios::trunc);
	for (int i = 0; i < maxSize / 64; i++)
	{
		for (int y = 0; y < 64; y++)
		{
			if (((1ULL << i) & bitArr[i]) != 0)
			{
				o_data << (y + 64 * i) << ' ';
			}
		}
	}
	i_data.close();
}
void P3::Task2()
{
	int maxSize = 10000000;
	maxSize /= (8 * 1024 * 1024);
	std::cout << maxSize << '\n';
}
