#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

struct UniversityRecord {
    int specialtyCode;        // Код специальности (ключ)
    char universityName[100]; // Название университета (фиксированная длина)
};
// Структура для хранения индексов
struct IndexRecord {
    int specialtyCode;
    long long offset; // Смещение записи в файле
};
// Функция для создания двоичного файла
void createBinaryFile(const string& filename, int numRecords) {
    srand(time(0)); // Инициализация генератора случайных чисел
    ofstream outFile(filename, ios::binary);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < numRecords; i++) {
        UniversityRecord record;
        record.specialtyCode = rand() % 10000 + 1000; // Генерация случайного кода специальности

        // Генерация случайного названия университета
        string universityNames[] = { "Moscow State University", "St. Petersburg University", "Novosibirsk State University", "Tomsk State University", "Kazan Federal University" };
        string name = universityNames[rand() % 5];
        strncpy(record.universityName, name.c_str(), sizeof(record.universityName) - 1);
        record.universityName[sizeof(record.universityName) - 1] = '\0'; // Завершающий нулевой символ

        // Запись записи в файл
        outFile.write(reinterpret_cast<char*>(&record), sizeof(record));
    }

    outFile.close();
    cout << "Binary file created with " << numRecords << " records." << endl;
}
// Функция линейного поиска
UniversityRecord* linearSearch(const string& filename, int key) {
    ifstream inFile(filename, ios::binary);  // Открытие файла в бинарном режиме

    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return nullptr;  // Если файл не открылся, возвращаем nullptr
    }

    UniversityRecord record;

    // Чтение записей из файла до конца
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (record.specialtyCode == key) {
            inFile.close();  // Закрытие файла после поиска
            return new UniversityRecord(record);  // Найдена запись, возвращаем указатель на запись
        }
    }

    inFile.close();  // Закрытие файла, если запись не найдена
    return nullptr;  // Запись не найдена, возвращаем nullptr
}
void printBin(const string& filename) {
    ifstream inFile(filename, ios::binary);  // Открытие файла в бинарном режиме

    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    UniversityRecord record;

    // Чтение записей из файла до конца
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        cout << UniversityRecord(record).specialtyCode << " / " << UniversityRecord(record).universityName << endl;
    }
}

// Функция для создания индекса
void createIndex(const string& filename, vector<IndexRecord>& indexTable) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    UniversityRecord record;
    long long offset = 0;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        IndexRecord index;
        index.specialtyCode = record.specialtyCode;
        index.offset = offset;
        indexTable.push_back(index);
        offset += sizeof(record);
    }

    inFile.close();
}

// Функция бинарного поиска по индексу
long long binarySearchIndex(const vector<IndexRecord>& indexTable, int key) {
    int left = 0, right = indexTable.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        //cout << mid << " " << indexTable[mid].specialtyCode << "/" << key << endl;

        if (indexTable[mid].specialtyCode == key) {
            return indexTable[mid].offset;
        }
        if (indexTable[mid].specialtyCode < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Запись не найдена
}

// Функция для чтения записи из файла по смещению
UniversityRecord readRecordAtOffset(const string& filename, long long offset) {
    ifstream inFile(filename, ios::binary);
    UniversityRecord record;
    inFile.seekg(offset);
    inFile.read(reinterpret_cast<char*>(&record), sizeof(record));
    inFile.close();
    return record;
}


int mainCreateBin() {
    string filename = "test.dat";
    createBinaryFile(filename, 100); // Создаем файл с 100 записями
    return 0;
}
int mainPrint() {
    string filename = "test.dat";  // Имя файла

    clock_t start = clock();
    printBin(filename);
    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Search time: " << duration << " seconds." << endl;

    return 0;
}

int main2() {
    string filename = "test.dat";  // Имя файла
    int key = 7953;  // Пример кода специальности для поиска

    // Замер времени выполнения поиска
    clock_t start = clock();
    UniversityRecord* record = linearSearch(filename, key);
    clock_t end = clock();

    if (record) {
        cout << "Record found: " << record->universityName << endl;
        delete record;  // Освобождение памяти
    }
    else {
        cout << "Record not found." << endl;
    }

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Search time: " << duration << " seconds." << endl;

    return 0;
}
int main3() {
    string filename = "test.dat";
    vector<IndexRecord> indexTable;

    // Создаем индекс
    createIndex(filename, indexTable);

    // Поиск по ключу
    int key = 3676; // Пример кода специальности для поиска
    clock_t start = clock();
    long long offset = binarySearchIndex(indexTable, key);
    clock_t end = clock();

    if (offset != -1) {
        UniversityRecord record = readRecordAtOffset(filename, offset);
        cout << "Record found: " << record.universityName << endl;
    }
    else {
        cout << "Record not found." << endl;
    }

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Search time: " << duration << " seconds." << endl;

    return 0;
}
