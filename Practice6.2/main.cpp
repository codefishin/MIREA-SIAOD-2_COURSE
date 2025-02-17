#include <iostream>
#include <sstream>
#include <string>
#include <cctype>   // для ispunct
#include <Windows.h>
#include <algorithm>
#include <vector>
using namespace std;

int main1() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Ввод предложения с клавиатуры
    cout << "Введите предложение: ";
    string sentence;
    getline(cin, sentence);

    // Ввод слова, которое необходимо удалить из предложения
    cout << "Введите слово, которое нужно удалить: ";
    string target;
    cin >> target;

    // Заменяем все знаки препинания на пробелы,
    // чтобы разделить слова корректно.
    for (char& c : sentence) {
        if (ispunct(c)) {
            c = ' ';
        }
    }

    // Используем istringstream для разбиения строки на слова.
    istringstream iss(sentence);
    string word;
    string result;
    bool firstWord = true;

    // Обрабатываем все слова, найденные в предложении.
    while (iss >> word) {
        // Если слово совпадает с заданным, пропускаем его.
        if (word == target) {
            continue;
        }
        // Для первого слова не добавляем пробел перед ним
        if (!firstWord) {
            result += " ";
        }
        result += word;
        firstWord = false;
    }

    // Вывод результата
    cout << "Изменённое предложение: " << result << endl;

    return 0;
}

// Функция для вычисления префикс-функции
vector<int> computeKMPTable(const string& s) {
    int n = s.length();
    vector<int> kmpTable(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = kmpTable[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = kmpTable[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        kmpTable[i] = j;
    }
    return kmpTable;
}

// Функция для нахождения максимального палиндрома
string findLongestPalindrome(const string& s) {
    string reversedS = s;
    reverse(reversedS.begin(), reversedS.end());

    string combined = s + "#" + reversedS; // Формируем строку для проверки
    vector<int> kmpTable = computeKMPTable(combined);

    int maxLen = 0;
    int maxIdx = 0;

    // Проходим по префикс-функции для нахождения максимальной длины палиндрома
    for (int i = 0; i < kmpTable.size(); ++i) {
        if (kmpTable[i] > maxLen && i - kmpTable[i] < s.length()) {
            maxLen = kmpTable[i];
            maxIdx = i;
        }
    }

    return s.substr(maxIdx - maxLen, maxLen);
}
int main2() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string s;
    cout << "Введите строку: ";
    getline(cin, s);

    string palindrome = findLongestPalindrome(s);
    cout << "Максимальный палиндром: " << palindrome << endl;

    return 0;
}
