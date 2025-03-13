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
bool isPalindrome(const string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}
string findLongestPalindrome(const string& text) {
    int maxLength = 0;
    string longestPalindrome;
    for (int i = 0; i < text.size(); i++) {
        for (int j = i; j < text.size(); j++) {
            string subStr = text.substr(i, j - i + 1);
            if (isPalindrome(subStr) && subStr.size() > maxLength) {
                maxLength = subStr.size();
                longestPalindrome = subStr;
            }
        }
    }
    return longestPalindrome;
}
int main51() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string s;
    cout << "Введите строку: ";
    getline(cin, s);
    string palindrome = findLongestPalindrome(s);
    cout << "Максимальный палиндром: " << palindrome << endl;

    return 0;
}
